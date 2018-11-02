#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/generate.h"
#include "../include/parser.tab.h"

static int global_offset = 0;
static int local_offset = 0;
static int register_offset = 0;
static int label_offset = 0;

const char* instruction[] = {[STORE_AI] = "storeAI %s => %s, %d\n",
                             [LOAD_I] = "loadI %d => %s\n",
                             [LOAD_AI] = "loadAI %s, %d => %s\n",
                             [ADD] = "add %s, %s => %s\n",
                             [SUB] = "sub %s, %s => %s\n",
                             [MULT] = "mult %s, %s => %s\n",
                             [DIV] = "div %s, %s => %s\n",
                             [CMP_LT] = "cmp_LT %s, %s -> %s\n",
                             [CMP_LE] = "cmp_LE %s, %s -> %s\n",
                             [CMP_GT] = "cmp_GT %s, %s -> %s\n",
                             [CMP_GE] = "cmp_GE %s, %s -> %s\n",
                             [CMP_EQ] = "cmp_EQ %s, %s -> %s\n",
                             [CMP_NE] = "cmp_NE %s, %s -> %s\n",
                             [CBR] = "cbr %s -> %s, %s\n",
                             [JUMP_I] = "jumpI -> %s\n",
                             [LABEL] = "%s:\n"};

struct offset_table* alloc_offset_table() {
    struct offset_table* table = malloc(sizeof *table);
    table->head = 0;
    return table;
}

void free_address(struct address* addr) {
    if (addr != 0) {
        free_address(addr->next);
        free(addr);
    }
}

void free_offset_table(struct offset_table* table) {
    free_address(table->head);
    free(table);
};

void generate_code(struct node* node) {
    struct offset_table* table = alloc_offset_table();
    generate(node, table, 0, 0);
    printf("halt\n");

    free_offset_table(table);
}

void generate(struct node* node,
              struct offset_table* table,
              char* l_true,
              char* l_false) {
    if (node != 0) {
        switch (node->type) {
            case N_LITERAL:
                generate_literal(node->val.token);
                break;
            case N_BINARY_EXP:
                generate_binary(node->val.binary_exp, table, l_true, l_false);
                break;
            case N_DO_WHILE:
                generate_do_while(node->val.do_while_cmd, table);
                break;
            case N_WHILE:
                generate_while(node->val.while_cmd, table);
                break;
            case N_IF:
                generate_if(node->val.if_cmd, table);
                break;
            case N_VAR:
                generate_var(node->val.var, table);
                break;
            case N_ATTRIBUTION:
                generate(node->val.attr_cmd.exp, table, 0, 0);
                generate_attribution(node->val.attr_cmd, table);
                break;
            case N_LOCAL_VAR_DECL:
                generate(node->val.local_var_decl.init, table, 0, 0);
                generate_local_var(node->val.local_var_decl, table);
                break;
            case N_CMD_BLOCK:
                generate(node->val.cmd_block.high_list, table, 0, 0);
                break;
            case N_HIGH_LIST:
                generate(node->val.high_list.high_list, table, 0, 0);
                generate(node->val.high_list.cmd, table, 0, 0);
                break;
            case N_FUNCTION_DEF:
                generate(node->val.function_def.cmd_block, table, 0, 0);
                break;
            case N_GLOBAL_VAR_DECL:
                generate_global_var(node->val.global_var_decl, table);
                break;
            case N_UNIT:
                generate(node->val.unit.unit, table, 0, 0);
                generate(node->val.unit.element, table, 0, 0);
                break;
            default:
                break;
        }
    }
}

struct address* get_address(char* id, struct offset_table* table) {
    struct address* var = table->head;

    while (var != 0) {
        if (strcmp(id, var->id) == 0) {
            break;
        }

        var = var->next;
    }

    return var;
}

char* get_reg(int n) {
    char* reg = malloc(16 * sizeof *reg);
    snprintf(reg, 16 * sizeof *reg, "r%d", n);
    return reg;
}

char* get_label() {
    char* label = malloc(16 * sizeof *label);
    snprintf(label, 16 * sizeof *label, "l%d", label_offset);
    label_offset += 1;
    return label;
}

void generate_global_var(struct global_var_decl global_var,
                         struct offset_table* table) {
    struct address* var = malloc(sizeof *var);
    var->id = global_var.token.val.string_v;
    var->scope = GLOBAL;
    var->offset = global_offset;
    global_offset += 4;

    var->next = table->head;
    table->head = var;
}

void generate_local_var(struct local_var_decl local_var,
                        struct offset_table* table) {
    struct address* var = malloc(sizeof *var);
    var->id = local_var.token.val.string_v;
    var->scope = LOCAL;
    var->offset = local_offset;
    local_offset += 4;

    var->next = table->head;
    table->head = var;

    if (local_var.init != 0) {
        char* reg = get_reg(register_offset - 1);
        printf(instruction[STORE_AI], reg, "rfp", var->offset);
        free(reg);
    }
}

void generate_attribution(struct attr_cmd attr, struct offset_table* table) {
    struct address* var =
        get_address(attr.var->val.var.token.val.string_v, table);

    char* reg = get_reg(register_offset - 1);

    if (var->scope == GLOBAL) {
        printf(instruction[STORE_AI], reg, "rbss", var->offset);
    } else {
        printf(instruction[STORE_AI], reg, "rfp", var->offset);
    }

    free(reg);
}

void generate_literal(struct token literal) {
    int val = literal.val.int_v;
    char* reg = get_reg(register_offset);
    register_offset += 1;

    printf(instruction[LOAD_I], val, reg);
    free(reg);
}

void generate_var(struct var var, struct offset_table* table) {
    struct address* addr = get_address(var.token.val.string_v, table);
    char* reg = get_reg(register_offset);
    register_offset += 1;

    if (addr->scope == GLOBAL) {
        printf(instruction[LOAD_AI], "rbss", addr->offset, reg);
    } else {
        printf(instruction[LOAD_AI], "rfp", addr->offset, reg);
    }

    free(reg);
}

void generate_binary(struct binary_exp binary_exp,
                     struct offset_table* table,
                     char* l_true,
                     char* l_false) {
    if (binary_exp.op == AND_OP) {
        char* l_and = get_label();
        generate(binary_exp.left, table, l_and, l_false);
        printf(instruction[LABEL], l_and);
        generate(binary_exp.right, table, l_true, l_false);
        free(l_and);
    } else if (binary_exp.op == OR_OP) {
        char* l_or = get_label();
        generate(binary_exp.left, table, l_true, l_or);
        printf(instruction[LABEL], l_or);
        generate(binary_exp.right, table, l_true, l_false);
        free(l_or);
    } else {
        generate(binary_exp.left, table, l_true, l_false);
        char* reg1 = get_reg(register_offset - 1);
        generate(binary_exp.right, table, l_true, l_false);
        char* reg2 = get_reg(register_offset - 1);

        char* reg3 = get_reg(register_offset);
        register_offset += 1;
        switch (binary_exp.op) {
            case '+':
                printf(instruction[ADD], reg1, reg2, reg3);
                break;
            case '-':
                printf(instruction[SUB], reg1, reg2, reg3);
                break;
            case '*':
                printf(instruction[MULT], reg1, reg2, reg3);
                break;
            case '/':
                printf(instruction[DIV], reg1, reg2, reg3);
                break;
            case '<':
                printf(instruction[CMP_LT], reg1, reg2, reg3);
                printf(instruction[CBR], reg3, l_true, l_false);
                break;
            case '>':
                printf(instruction[CMP_GT], reg1, reg2, reg3);
                printf(instruction[CBR], reg3, l_true, l_false);
                break;
            case LE_OP:
                printf(instruction[CMP_LE], reg1, reg2, reg3);
                printf(instruction[CBR], reg3, l_true, l_false);
                break;
            case GE_OP:
                printf(instruction[CMP_GE], reg1, reg2, reg3);
                printf(instruction[CBR], reg3, l_true, l_false);
                break;
            case EQ_OP:
                printf(instruction[CMP_EQ], reg1, reg2, reg3);
                printf(instruction[CBR], reg3, l_true, l_false);
                break;
            case NE_OP:
                printf(instruction[CMP_NE], reg1, reg2, reg3);
                printf(instruction[CBR], reg3, l_true, l_false);
                break;
            default:
                break;
        }

        free(reg1);
        free(reg2);
        free(reg3);
    }
}

void generate_if(struct if_cmd if_cmd, struct offset_table* table) {
    char* l_true = get_label();
    char* l_false = get_label();
    char* l_done = get_label();

    generate(if_cmd.condition, table, l_true, l_false);
    printf(instruction[LABEL], l_true);
    generate(if_cmd.then_cmd_block, table, 0, 0);
    printf(instruction[JUMP_I], l_done);
    printf(instruction[LABEL], l_false);
    generate(if_cmd.else_cmd_block, table, 0, 0);
    printf(instruction[LABEL], l_done);

    free(l_true);
    free(l_false);
    free(l_done);
}

void generate_while(struct while_cmd while_cmd, struct offset_table* table) {
    char* l_true = get_label();
    char* l_false = get_label();
    char* l_begin = get_label();

    printf(instruction[LABEL], l_begin);
    generate(while_cmd.condition, table, l_true, l_false);
    printf(instruction[LABEL], l_true);
    generate(while_cmd.cmd_block, table, 0, 0);
    printf(instruction[JUMP_I], l_begin);
    printf(instruction[LABEL], l_false);

    free(l_true);
    free(l_false);
    free(l_begin);
}

void generate_do_while(struct do_while_cmd do_while_cmd,
                       struct offset_table* table) {
    char* l_true = get_label();
    char* l_false = get_label();

    printf(instruction[LABEL], l_true);
    generate(do_while_cmd.cmd_block, table, 0, 0);
    generate(do_while_cmd.condition, table, l_true, l_false);
    printf(instruction[LABEL], l_false);

    free(l_true);
    free(l_false);
}

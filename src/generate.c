#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/generate.h"
#include "../include/parser.tab.h"

static int global_offset = 0;
static int local_offset = 0;
static int register_offset = 0;
static int label_offset = 0;
static int ins = 0;

struct code code;

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
                             [JUMP] = "jump -> %s\n",
                             [LABEL] = "%s:\n",
                             [FLABEL] = "l%s:\n",
                             [I2I] = "i2i %s => %s\n",
                             [ADD_I] = "addI %s, %d => %s\n"};

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
    code.head = 0;
    code.last = 0;

    char* line = alloc_line();
    sprintf(line, instruction[LOAD_I], 1024, "rfp");
    append_ins(line);
    ins++;

    line = alloc_line();
    sprintf(line, instruction[LOAD_I], 1024, "rsp");
    append_ins(line);
    ins++;

    line = alloc_line();
    sprintf(line, instruction[LOAD_I], 0, "rbss");
    append_ins(line);
    ins++;

    line = alloc_line();
    sprintf(line, instruction[JUMP_I], "lmain");
    append_ins(line);
    ins++;

    generate(node, table, 0, 0);

    print_code();
    free_code(code.head);

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
            case N_RETURN:
                generate_return(node->val.return_cmd, table);
                break;
            case N_FUNCTION:
                generate_function(node->val.function_cmd, table);
                break;
            case N_CMD_BLOCK:
                generate(node->val.cmd_block.high_list, table, 0, 0);
                break;
            case N_HIGH_LIST:
                generate(node->val.high_list.high_list, table, 0, 0);
                generate(node->val.high_list.cmd, table, 0, 0);
                break;
            case N_FUNCTION_DEF:
                generate_function_def(node->val.function_def, table);
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

char* get_flabel(char* name) {
    char* label = malloc(64 * sizeof *label);
    snprintf(label, 64 * sizeof *label, "l%s", name);
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
        char* line = alloc_line();
        sprintf(line, instruction[STORE_AI], reg, "rfp", var->offset);
        append_ins(line);
        ins++;
        free(reg);
    }
}

void generate_attribution(struct attr_cmd attr, struct offset_table* table) {
    struct address* var =
        get_address(attr.var->val.var.token.val.string_v, table);

    char* reg = get_reg(register_offset - 1);

    char* line = alloc_line();
    if (var->scope == GLOBAL) {
        sprintf(line, instruction[STORE_AI], reg, "rbss", var->offset);
    } else {
        sprintf(line, instruction[STORE_AI], reg, "rfp", var->offset);
    }
    append_ins(line);
    ins++;

    free(reg);
}

void generate_literal(struct token literal) {
    int val = literal.val.int_v;
    char* reg = get_reg(register_offset);
    register_offset += 1;

    char* line = alloc_line();
    sprintf(line, instruction[LOAD_I], val, reg);
    append_ins(line);
    ins++;
    free(reg);
}

void generate_var(struct var var, struct offset_table* table) {
    struct address* addr = get_address(var.token.val.string_v, table);
    char* reg = get_reg(register_offset);
    register_offset += 1;

    char* line = alloc_line();
    if (addr->scope == GLOBAL) {
        sprintf(line, instruction[LOAD_AI], "rbss", addr->offset, reg);
    } else {
        sprintf(line, instruction[LOAD_AI], "rfp", addr->offset, reg);
    }
    append_ins(line);
    ins++;

    free(reg);
}

void generate_binary(struct binary_exp binary_exp,
                     struct offset_table* table,
                     char* l_true,
                     char* l_false) {
    if (binary_exp.op == AND_OP) {
        char* l_and = get_label();
        generate(binary_exp.left, table, l_and, l_false);
        char* line = alloc_line();
        sprintf(line, instruction[LABEL], l_and);
        append_ins(line);
        generate(binary_exp.right, table, l_true, l_false);
        free(l_and);
    } else if (binary_exp.op == OR_OP) {
        char* l_or = get_label();
        generate(binary_exp.left, table, l_true, l_or);
        char* line = alloc_line();
        sprintf(line, instruction[LABEL], l_or);
        append_ins(line);
        generate(binary_exp.right, table, l_true, l_false);
        free(l_or);
    } else {
        generate(binary_exp.left, table, l_true, l_false);
        char* reg1 = get_reg(register_offset - 1);
        generate(binary_exp.right, table, l_true, l_false);
        char* reg2 = get_reg(register_offset - 1);

        char* reg3 = get_reg(register_offset);
        register_offset += 1;

        char* line = alloc_line();
        switch (binary_exp.op) {
            case '+':
                sprintf(line, instruction[ADD], reg1, reg2, reg3);
                append_ins(line);
                ins++;
                break;
            case '-':
                sprintf(line, instruction[SUB], reg1, reg2, reg3);
                append_ins(line);
                ins++;
                break;
            case '*':
                sprintf(line, instruction[MULT], reg1, reg2, reg3);
                append_ins(line);
                ins++;
                break;
            case '/':
                sprintf(line, instruction[DIV], reg1, reg2, reg3);
                append_ins(line);
                ins++;
                break;
            case '<':
                sprintf(line, instruction[CMP_LT], reg1, reg2, reg3);
                append_ins(line);
                ins++;
                line = alloc_line();
                sprintf(line, instruction[CBR], reg3, l_true, l_false);
                append_ins(line);
                ins++;
                break;
            case '>':
                sprintf(line, instruction[CMP_GT], reg1, reg2, reg3);
                append_ins(line);
                ins++;
                line = alloc_line();
                sprintf(line, instruction[CBR], reg3, l_true, l_false);
                append_ins(line);
                ins++;
                break;
            case LE_OP:
                sprintf(line, instruction[CMP_LE], reg1, reg2, reg3);
                append_ins(line);
                ins++;
                line = alloc_line();
                sprintf(line, instruction[CBR], reg3, l_true, l_false);
                append_ins(line);
                ins++;
                break;
            case GE_OP:
                sprintf(line, instruction[CMP_GE], reg1, reg2, reg3);
                append_ins(line);
                ins++;
                line = alloc_line();
                sprintf(line, instruction[CBR], reg3, l_true, l_false);
                append_ins(line);
                ins++;
                break;
            case EQ_OP:
                sprintf(line, instruction[CMP_EQ], reg1, reg2, reg3);
                append_ins(line);
                ins++;
                line = alloc_line();
                sprintf(line, instruction[CBR], reg3, l_true, l_false);
                append_ins(line);
                ins++;
                break;
            case NE_OP:
                sprintf(line, instruction[CMP_NE], reg1, reg2, reg3);
                append_ins(line);
                ins++;
                line = alloc_line();
                sprintf(line, instruction[CBR], reg3, l_true, l_false);
                append_ins(line);
                ins++;
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
    char* line = alloc_line();
    sprintf(line, instruction[LABEL], l_true);
    append_ins(line);
    generate(if_cmd.then_cmd_block, table, 0, 0);
    line = alloc_line();
    sprintf(line, instruction[JUMP_I], l_done);
    append_ins(line);
    ins++;
    line = alloc_line();
    sprintf(line, instruction[LABEL], l_false);
    append_ins(line);
    generate(if_cmd.else_cmd_block, table, 0, 0);
    line = alloc_line();
    sprintf(line, instruction[LABEL], l_done);
    append_ins(line);

    free(l_true);
    free(l_false);
    free(l_done);
}

void generate_while(struct while_cmd while_cmd, struct offset_table* table) {
    char* l_true = get_label();
    char* l_false = get_label();
    char* l_begin = get_label();

    char* line = alloc_line();
    sprintf(line, instruction[LABEL], l_begin);
    append_ins(line);
    generate(while_cmd.condition, table, l_true, l_false);
    line = alloc_line();
    sprintf(line, instruction[LABEL], l_true);
    append_ins(line);
    generate(while_cmd.cmd_block, table, 0, 0);
    line = alloc_line();
    sprintf(line, instruction[JUMP_I], l_begin);
    append_ins(line);
    ins++;
    line = alloc_line();
    sprintf(line, instruction[LABEL], l_false);
    append_ins(line);

    free(l_true);
    free(l_false);
    free(l_begin);
}

void generate_do_while(struct do_while_cmd do_while_cmd,
                       struct offset_table* table) {
    char* l_true = get_label();
    char* l_false = get_label();

    char* line = alloc_line();
    sprintf(line, instruction[LABEL], l_true);
    append_ins(line);
    generate(do_while_cmd.cmd_block, table, 0, 0);
    generate(do_while_cmd.condition, table, l_true, l_false);
    line = alloc_line();
    sprintf(line, instruction[LABEL], l_false);
    append_ins(line);

    free(l_true);
    free(l_false);
}

void generate_function_def(struct function_def function_def,
                           struct offset_table* table) {
    char* line = alloc_line();
    sprintf(line, instruction[FLABEL], function_def.token.val.string_v);
    append_ins(line);

    bool is_main = strcmp(function_def.token.val.string_v, "main") == 0;

    if (!is_main) {
        line = alloc_line();
        sprintf(line, instruction[STORE_AI], "rsp", "rsp", 4);
        append_ins(line);
        ins++;

        line = alloc_line();
        sprintf(line, instruction[STORE_AI], "rfp", "rsp", 8);
        append_ins(line);
        ins++;

        line = alloc_line();
        sprintf(line, instruction[I2I], "rsp", "rfp");
        append_ins(line);
        ins++;

        local_offset = 16;
    } else {
        local_offset = 0;
    }

    char* addI = alloc_line();
    append_ins(addI);
    ins++;

    struct node* param = function_def.params;
    struct address* var = 0;
    while (param != 0) {
        var = malloc(sizeof *var);
        var->id = param->val.parameter.token.val.string_v;
        var->scope = LOCAL;
        var->offset = local_offset;
        local_offset += 4;

        var->next = table->head;
        table->head = var;

        param = param->val.parameter.next;
    }

    register_offset = 0;
    generate(function_def.cmd_block, table, 0, 0);

    sprintf(addI, instruction[ADD_I], "rsp", local_offset, "rsp");

    if (!is_main) {
        char *reg = get_reg(register_offset);
        register_offset++;

        line = alloc_line();
        sprintf(line, instruction[LOAD_AI], "rfp", 0, reg);
        append_ins(line);
        ins++;

        line = alloc_line();
        sprintf(line, instruction[LOAD_AI], "rfp", 4, "rsp");
        append_ins(line);
        ins++;

        line = alloc_line();
        sprintf(line, instruction[LOAD_AI], "rfp", 8, "rfp");
        append_ins(line);
        ins++;

        line = alloc_line();
        sprintf(line, instruction[JUMP], reg);
        append_ins(line);
        ins++;

        free(reg);
    } else {
        line = alloc_line();
        sprintf(line, "halt\n");
        append_ins(line);
        ins++;
    }
}

void generate_return(struct return_cmd return_cmd, struct offset_table* table) {
    generate(return_cmd.exp, table, 0, 0);

    char* reg = get_reg(register_offset - 1);

    char* line = alloc_line();
    sprintf(line, instruction[STORE_AI], reg, "rfp", 12);
    append_ins(line);
    ins++;

    free(reg);

    reg = get_reg(register_offset);
    register_offset++;

    line = alloc_line();
    sprintf(line, instruction[LOAD_AI], "rfp", 0, reg);
    append_ins(line);
    ins++;

    line = alloc_line();
    sprintf(line, instruction[LOAD_AI], "rfp", 4, "rsp");
    append_ins(line);
    ins++;

    line = alloc_line();
    sprintf(line, instruction[LOAD_AI], "rfp", 8, "rfp");
    append_ins(line);
    ins++;

    line = alloc_line();
    sprintf(line, instruction[JUMP], reg);
    append_ins(line);
    ins++;

    free(reg);
}

void generate_function(struct function_cmd function_cmd,
                       struct offset_table* table) {

    struct node* arg = function_cmd.arg_list;
    char* reg;
    char* line;
    int param_offset = 16;
    while (arg != 0) {
        generate(arg->val.arg_list.arg, table, 0, 0);

        reg = get_reg(register_offset - 1);

        line = alloc_line();
        sprintf(line, instruction[STORE_AI], reg, "rsp", param_offset);
        append_ins(line);
        ins++;

        param_offset += 4;
        arg = arg->val.arg_list.next;

        free(reg);
    }

    char* rsp = alloc_line();
    append_ins(rsp);
    ins++;

    char* ins_reg = get_reg(register_offset);
    register_offset++;
    line = alloc_line();
    sprintf(line, instruction[STORE_AI], ins_reg, "rsp", 0);
    append_ins(line);
    ins++;

    int mem_offset = local_offset;
    int i;
    for (i = 0; i < register_offset; i++) {
        reg = get_reg(i);
        line = alloc_line();
        sprintf(line, instruction[STORE_AI], reg, "rfp", local_offset);
        append_ins(line);
        ins++;
        local_offset += 4;
        free(reg);
    }

    char* flabel = get_flabel(function_cmd.token.val.string_v);
    line = alloc_line();
    sprintf(line, instruction[JUMP_I], flabel);
    append_ins(line);
    ins++;
    free(flabel);

    sprintf(rsp, instruction[LOAD_I], ins, ins_reg);
    free(ins_reg);

    for (i = 0; i < register_offset; i++) {
        reg = get_reg(i);
        line = alloc_line();
        sprintf(line, instruction[LOAD_AI], "rfp", mem_offset, reg);
        append_ins(line);
        ins++;
        mem_offset += 4;
        free(reg);
    }

    reg = get_reg(register_offset);
    register_offset += 1;
    line = alloc_line();
    sprintf(line, instruction[LOAD_AI], "rsp", 12, reg);
    append_ins(line);
    ins++;
    free(reg);
}

char* alloc_line() {
    char* line = malloc(64 * sizeof *line);
    return line;
}

void append_ins(char* line) {
    struct ins* ins = malloc(sizeof *ins);
    ins->line = line;
    ins->next = 0;

    if (code.head == 0) {
        code.head = ins;
        code.last = ins;
    } else {
        code.last->next = ins;
        code.last = ins;
    }
}

void free_code(struct ins* head) {
    if (head != 0) {
        free(head->line);
        free_code(head->next);
    }

    free(head);
}

void print_code() {
    struct ins* ins = code.head;

    while (ins != 0) {
        printf("%s", ins->line);
        ins = ins->next;
    }
}

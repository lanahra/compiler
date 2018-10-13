#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/analyze.h"

const char* error_msg[] =
    {[ERROR_UNDECLARED] = "Identifier not declared: %s line %d column %d\n",
     [ERROR_ALREADY_DECLARED] =
         "Identifier already declared: %s line %d column %d\n"};

struct table* alloc_table() {
    struct table* table = malloc(sizeof *table);
    table->head = 0;
    return table;
}

void free_symbol(struct symbol* symbol) {
    if (symbol != 0) {
        free_symbol(symbol->next);

        switch (symbol->type) {
            case SYMBOL_CLASS_DEF:
                break;
            case SYMBOL_GLOBAL_VAR_DECL:
                break;
        }
    }

    free(symbol);
}

void free_table(struct table* table) {
    free_symbol(table->head);
    free(table);
}

bool is_declared(char* id, struct table* table) {
    struct symbol* symbol = table->head;

    while (symbol != 0) {
        if (strcmp(id, symbol->id) == 0) {
            return true;
        }

        symbol = symbol->next;
    }

    return false;
}

enum analyze_result analyze_node(struct node* node, struct table* table) {
    enum analyze_result result = SUCCESS;

    if (node != 0) {
        printf("%s\n", type_name[node->type]);
        switch (node->type) {
            case N_INT_LITERAL:
                break;
            case N_FLOAT_LITERAL:
                break;
            case N_CHAR_LITERAL:
                break;
            case N_STRING_LITERAL:
                break;
            case N_BOOL_LITERAL:
                break;
            case N_UNARY_EXP:
                break;
            case N_BINARY_EXP:
                break;
            case N_TERNARY_EXP:
                break;
            case N_EXP_LIST:
                break;
            case N_SWITCH:
                break;
            case N_DO_WHILE:
                break;
            case N_WHILE:
                break;
            case N_FOR:
                break;
            case N_FOREACH:
                break;
            case N_DOT_ARG:
                break;
            case N_ARG_LIST:
                break;
            case N_FUNCTION:
                break;
            case N_PIPE:
                break;
            case N_IF:
                break;
            case N_OUTPUT:
                break;
            case N_INPUT:
                break;
            case N_CASE:
                break;
            case N_RETURN:
                break;
            case N_SHIFT:
                break;
            case N_BREAK:
                break;
            case N_CONTINUE:
                break;
            case N_VAR:
                break;
            case N_ATTRIBUTION:
                break;
            case N_LOCAL_VAR_DECL:
                break;
            case N_CMD_LIST:
                break;
            case N_CMD_BLOCK:
                break;
            case N_HIGH_LIST:
                break;
            case N_PARAM:
                break;
            case N_FUNCTION_DEF:
                break;
            case N_FIELD:
                break;
            case N_CLASS_DEF:
                result = define_class(node->val.class_def, table);
                break;
            case N_GLOBAL_VAR_DECL:
                result = declare_global_var(node->val.global_var_decl, table);
                break;
            case N_UNIT:
                result = analyze_node(node->val.unit.unit, table);
                if (result == SUCCESS) {
                    result = analyze_node(node->val.unit.element, table);
                }
                break;
        }
    }

    return result;
}

enum analyze_result define_class(struct class_def class_def,
                                 struct table* table) {
    printf("define class: %s\n", class_def.token.val.string_v);
    if (is_declared(class_def.token.val.string_v, table)) {
        fprintf(stderr,
                error_msg[ERROR_ALREADY_DECLARED],
                class_def.token.val.string_v,
                class_def.token.line,
                class_def.token.column);
        return ERROR_ALREADY_DECLARED;
    }

    struct symbol* symbol = malloc(sizeof *symbol);
    symbol->id = class_def.token.val.string_v;
    symbol->type = SYMBOL_CLASS_DEF;
    symbol->data.fields_head = class_def.field_list;
    symbol->is_new_context = false;

    symbol->next = table->head;
    table->head = symbol;

    return SUCCESS;
}

enum analyze_result declare_global_var(struct global_var_decl global_var,
                                       struct table* table) {
    printf("declare global var: %s\n", global_var.token.val.string_v);
    if (is_declared(global_var.token.val.string_v, table)) {
        fprintf(stderr,
                error_msg[ERROR_ALREADY_DECLARED],
                global_var.token.val.string_v,
                global_var.token.line,
                global_var.token.column);
        return ERROR_ALREADY_DECLARED;
    }

    if (global_var.type.key == CUSTOM &&
        !is_declared(global_var.type.val.custom, table)) {
        fprintf(stderr,
                error_msg[ERROR_UNDECLARED],
                global_var.type.val.custom,
                global_var.token.line,
                global_var.token.column);
        return ERROR_UNDECLARED;
    }

    struct symbol* symbol = malloc(sizeof *symbol);
    symbol->id = global_var.token.val.string_v;
    symbol->type = SYMBOL_GLOBAL_VAR_DECL;
    symbol->data.type = global_var.type;
    symbol->is_new_context = false;

    symbol->next = table->head;
    table->head = symbol;

    return SUCCESS;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/analyze.h"
#include "../include/parser.tab.h"

const char* error_msg[] =
    {[ERROR_UNDECLARED] = "Identifier not declared: %s line %d column %d\n",
     [ERROR_ALREADY_DECLARED] =
         "Identifier already declared: %s line %d column %d\n",
     [ERROR_MISMATCHED_TYPE] =
         "Mismatched types: %s and %s line %d column %d\n",
     [ERROR_IMPLICIT_CONVERSION_STRING] =
         "Cannot convert %s to %s line %d column %d\n",
     [ERROR_IMPLICIT_CONVERSION_CHAR] =
         "Cannot convert %s to %s line %d column %d\n",
     [ERROR_IMPLICIT_CONVERSION_USER] =
         "Cannot convert %s to %s line %d column %d\n",
     [ERROR_IS_VARIABLE] =
         "Identifier %s must be used as a variable line %d column %d\n",
     [ERROR_IS_VECTOR] =
         "Identifier %s must be used as a vector line %d column %d\n",
     [ERROR_IS_USER] =
         "Identifier %s must be used as a class line %d column %d\n",
     [ERROR_IS_FUNCTION] =
         "Identifier %s must be used as a function line %d column %d\n",
     [ERROR_MISMATCHED_TYPE_RETURN] =
         "Wrong return type of function %s line %d column %d\n",
     [ERROR_MISSING_ARGS] =
         "Function call %s has missing arguments line %d column %d",
     [ERROR_TOO_MANY_ARGS] =
         "Function call %s has too many arguments line %d column %d"};

const char* literal_type[] = {[INT] = "int",
                              [FLOAT] = "string",
                              [CHAR] = "char",
                              [STRING] = "string",
                              [BOOL] = "bool"};

const struct type val_type[] =
    {[INT] = {.key = PRIMITIVE, .val.primitive = INT},
     [FLOAT] = {.key = PRIMITIVE, .val.primitive = FLOAT},
     [CHAR] = {.key = PRIMITIVE, .val.primitive = CHAR},
     [STRING] = {.key = PRIMITIVE, .val.primitive = STRING},
     [BOOL] = {.key = PRIMITIVE, .val.primitive = BOOL}};

struct table* alloc_table() {
    struct table* table = malloc(sizeof *table);
    table->head = 0;
    return table;
}

void free_symbol(struct symbol* symbol) {
    if (symbol != 0) {
        free_symbol(symbol->next);
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

bool is_type_defined(char* id, struct table* table) {
    struct symbol* symbol = table->head;

    while (symbol != 0) {
        if (strcmp(id, symbol->id) == 0) {
            return symbol->type == SYMBOL_CLASS_DEF ? true : false;
        }

        symbol = symbol->next;
    }

    return false;
}

struct symbol* get_symbol(char* id, struct table* table) {
    struct symbol* symbol = table->head;

    while (symbol != 0) {
        if (strcmp(id, symbol->id) == 0) {
            return symbol;
        }

        symbol = symbol->next;
    }

    return 0;
}

struct symbol* get_self_function(struct table* table) {
    struct symbol* symbol = table->head;

    while (symbol != 0) {
        if (symbol->type == SYMBOL_FUNCTION_DEF) {
            return symbol;
        }

        symbol = symbol->next;
    }

    return 0;
}

struct node* get_field(char* field, struct node* head) {
    struct node* node = head;

    while (node != 0) {
        if (strcmp(field, node->val.field.token.val.string_v) == 0) {
            return node;
        }

        node = node->val.field.next;
    }

    return 0;
}

struct analyze_result convert_type(struct type type, struct type target) {
    struct analyze_result result;
    if (type.key == CUSTOM && target.key == CUSTOM) {
        if (strcmp(type.val.custom, target.val.custom) == 0) {
            result.status = SUCCESS;
            return result;
        } else {
            result.status = ERROR_IMPLICIT_CONVERSION_USER;
            return result;
        }
    } else if (type.key == CUSTOM || target.key == CUSTOM) {
        result.status = ERROR_IMPLICIT_CONVERSION_USER;
        return result;
    } else if (type.val.primitive == target.val.primitive) {
        result.status = SUCCESS;
        return result;
    }

    switch (type.val.primitive) {
        case INT:
            if (target.val.primitive == FLOAT || target.val.primitive == BOOL) {
                result.status = SUCCESS;
                return result;
            }
            break;
        case FLOAT:
            if (target.val.primitive == INT || target.val.primitive == BOOL) {
                result.status = SUCCESS;
                return result;
            }
            break;
        case BOOL:
            if (target.val.primitive == FLOAT || target.val.primitive == INT) {
                result.status = SUCCESS;
                return result;
            }
            break;
        case CHAR:
            result.status = ERROR_IMPLICIT_CONVERSION_CHAR;
            return result;
        case STRING:
            result.status = ERROR_IMPLICIT_CONVERSION_STRING;
            return result;
    }

    if (target.val.primitive == CHAR) {
        result.status = ERROR_IMPLICIT_CONVERSION_CHAR;
        return result;
    }

    if (target.val.primitive == STRING) {
        result.status = ERROR_IMPLICIT_CONVERSION_STRING;
        return result;
    }

    result.status = ERROR_MISMATCHED_TYPE;
    return result;
}

struct analyze_result infer_type(struct type left, struct type right) {
    struct analyze_result result;
    result.status = SUCCESS;

    if (left.key != right.key) {
        result.status = ERROR_MISMATCHED_TYPE;
        return result;
    }

    if (left.key == CUSTOM) {
        if (strcmp(left.val.custom, right.val.custom) != 0) {
            result.status = ERROR_MISMATCHED_TYPE;
        } else {
            result.type = left;
        }
    } else {
        if (left.val.primitive == right.val.primitive) {
            result.type = left;
        } else if (left.val.primitive == CHAR || left.val.primitive == STRING ||
                   right.val.primitive == CHAR ||
                   right.val.primitive == STRING) {
            result.status = ERROR_MISMATCHED_TYPE;
        } else if (left.val.primitive == FLOAT ||
                   right.val.primitive == FLOAT) {
            result.type = val_type[FLOAT];
        } else if (left.val.primitive == INT || right.val.primitive == INT) {
            result.type = val_type[INT];
        } else {
            result.status = ERROR_MISMATCHED_TYPE;
        }
    }

    return result;
}

struct analyze_result match_access(enum var_access use,
                                   enum var_access symbol) {
    struct analyze_result result;
    result.status = SUCCESS;
    if (use != symbol && !(use == ACCESS_PRIMITIVE && symbol == ACCESS_CLASS)) {
        switch (symbol) {
            case ACCESS_PRIMITIVE:
                result.status = ERROR_IS_VARIABLE;
                break;
            case ACCESS_CLASS:
                result.status = ERROR_IS_USER;
                break;
            case ACCESS_PRIMITIVE_ARRAY:
            case ACCESS_CLASS_ARRAY:
                result.status = ERROR_IS_VECTOR;
                break;
            case ACCESS_FUNCTION:
                result.status = ERROR_IS_FUNCTION;
                break;
        }
    }

    return result;
}

struct analyze_result analyze_node(struct node* node, struct table* table) {
    struct analyze_result result;
    result.status = SUCCESS;

    if (node != 0) {
        printf("%s\n", type_name[node->type]);
        switch (node->type) {
            case N_LITERAL:
                result.type.key = PRIMITIVE;
                result.type.val.primitive = node->val.token.type;
                break;
            case N_UNARY_EXP:
                result = analyze_node(node->val.unary_exp.operand, table);
                break;
            case N_BINARY_EXP:
                result = analyze_binary(node->val.binary_exp, table);
                break;
            case N_TERNARY_EXP:
                result = analyze_ternary(node->val.ternary_exp, table);
                break;
            case N_EXP_LIST:
                break;
            case N_SWITCH:
                result = analyze_node(node->val.switch_cmd.control_exp, table);
                if (result.status != SUCCESS) {
                    return result;
                }
                result = convert_type(result.type, val_type[INT]);
                if (result.status != SUCCESS) {
                    return result;
                }
                result = analyze_node(node->val.switch_cmd.cmd_block, table);
                break;
            case N_DO_WHILE:
                result = analyze_node(node->val.do_while_cmd.cmd_block, table);
                if (result.status != SUCCESS) {
                    return result;
                }
                result = analyze_node(node->val.do_while_cmd.condition, table);
                if (result.status != SUCCESS) {
                    return result;
                }
                result = convert_type(result.type, val_type[BOOL]);
                break;
            case N_WHILE:
                result = analyze_node(node->val.while_cmd.condition, table);
                if (result.status != SUCCESS) {
                    return result;
                }
                result = convert_type(result.type, val_type[BOOL]);
                if (result.status != SUCCESS) {
                    return result;
                }
                result = analyze_node(node->val.while_cmd.cmd_block, table);
                break;
            case N_FOR:
                result = analyze_for(node->val.for_cmd, table);
                break;
            case N_FOREACH:
                break;
            case N_DOT_ARG:
                break;
            case N_ARG_LIST:
                break;
            case N_FUNCTION:
                result = analyze_function(node->val.function_cmd, table);
                break;
            case N_PIPE:
                break;
            case N_IF:
                result = analyze_node(node->val.if_cmd.condition, table);
                if (result.status != SUCCESS) {
                    return result;
                }
                result = convert_type(result.type, val_type[BOOL]);
                if (result.status != SUCCESS) {
                    return result;
                }
                result = analyze_node(node->val.if_cmd.then_cmd_block, table);
                if (result.status != SUCCESS) {
                    return result;
                }
                result = analyze_node(node->val.if_cmd.else_cmd_block, table);
                break;
            case N_OUTPUT:
                break;
            case N_INPUT:
                break;
            case N_CASE:
                break;
            case N_RETURN:
                result = analyze_return(node->val.return_cmd, table);
                break;
            case N_SHIFT:
                result = analyze_shift(node->val.shift_cmd, table);
                break;
            case N_BREAK:
                break;
            case N_CONTINUE:
                break;
            case N_VAR:
                result = analyze_var(node->val.var, table);
                break;
            case N_ATTRIBUTION:
                result = analyze_attr(node->val.attr_cmd, table);
                break;
            case N_LOCAL_VAR_DECL:
                result = declare_local_var(node->val.local_var_decl, table);
                break;
            case N_CMD_LIST:
                result = analyze_node(node->val.cmd_list.cmd_list, table);
                if (result.status == SUCCESS) {
                    result = analyze_node(node->val.cmd_list.cmd, table);
                }
                break;
            case N_CMD_BLOCK:
                result = analyze_node(node->val.cmd_block.high_list, table);
                break;
            case N_HIGH_LIST:
                result = analyze_node(node->val.high_list.high_list, table);
                if (result.status == SUCCESS) {
                    result = analyze_node(node->val.high_list.cmd, table);
                }
                break;
            case N_PARAM:
                break;
            case N_FUNCTION_DEF:
                result = define_function(node->val.function_def, table);
                if (result.status == SUCCESS) {
                    result =
                        analyze_node(node->val.function_def.cmd_block, table);
                }
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
                if (result.status == SUCCESS) {
                    result = analyze_node(node->val.unit.element, table);
                }
                break;
        }
    }

    return result;
}

struct analyze_result define_class(struct class_def class_def,
                                   struct table* table) {
    struct analyze_result result;
    result.status = SUCCESS;
    printf("define class: %s\n", class_def.token.val.string_v);
    if (is_declared(class_def.token.val.string_v, table)) {
        fprintf(stderr,
                error_msg[ERROR_ALREADY_DECLARED],
                class_def.token.val.string_v,
                class_def.token.line,
                class_def.token.column);
        result.status = ERROR_ALREADY_DECLARED;
        return result;
    }

    struct symbol* symbol = malloc(sizeof *symbol);
    symbol->id = class_def.token.val.string_v;
    symbol->type = SYMBOL_CLASS_DEF;
    symbol->data.class_def = class_def;
    symbol->is_new_context = false;

    symbol->next = table->head;
    table->head = symbol;

    return result;
}

struct analyze_result declare_global_var(struct global_var_decl global_var,
                                         struct table* table) {
    struct analyze_result result;
    result.status = SUCCESS;
    printf("declare global var: %s\n", global_var.token.val.string_v);
    if (is_declared(global_var.token.val.string_v, table)) {
        fprintf(stderr,
                error_msg[ERROR_ALREADY_DECLARED],
                global_var.token.val.string_v,
                global_var.token.line,
                global_var.token.column);
        result.status = ERROR_ALREADY_DECLARED;
        return result;
    }

    if (global_var.type.key == CUSTOM &&
        !is_type_defined(global_var.type.val.custom, table)) {
        fprintf(stderr,
                error_msg[ERROR_UNDECLARED],
                global_var.type.val.custom,
                global_var.token.line,
                global_var.token.column);
        result.status = ERROR_UNDECLARED;
        return result;
    }

    struct symbol* symbol = malloc(sizeof *symbol);
    symbol->id = global_var.token.val.string_v;
    symbol->type = SYMBOL_GLOBAL_VAR_DECL;
    symbol->data.global_var_decl = global_var;
    symbol->is_new_context = false;

    if (global_var.type.key == CUSTOM) {
        if (global_var.size == -1) {
            symbol->var_access = ACCESS_CLASS;
        } else {
            symbol->var_access = ACCESS_CLASS_ARRAY;
        }
    } else {
        if (global_var.size == -1) {
            symbol->var_access = ACCESS_PRIMITIVE;
        } else {
            symbol->var_access = ACCESS_PRIMITIVE_ARRAY;
        }
    }

    symbol->next = table->head;
    table->head = symbol;

    return result;
}

struct analyze_result define_params(struct node* params, struct table* table) {
    struct analyze_result result;
    result.status = SUCCESS;
    if (params != 0) {
        struct parameter param = params->val.parameter;
        printf("define param %s\n", param.token.val.string_v);
        if (is_declared(param.token.val.string_v, table)) {
            fprintf(stderr,
                    error_msg[ERROR_ALREADY_DECLARED],
                    param.token.val.string_v,
                    param.token.line,
                    param.token.column);
            result.status = ERROR_ALREADY_DECLARED;
            return result;
        }

        if (param.type.key == CUSTOM &&
            !is_type_defined(param.type.val.custom, table)) {
            fprintf(stderr,
                    error_msg[ERROR_UNDECLARED],
                    param.type.val.custom,
                    param.token.line,
                    param.token.column);
            result.status = ERROR_UNDECLARED;
            return result;
        }

        struct symbol* symbol = malloc(sizeof *symbol);
        symbol->id = param.token.val.string_v;
        symbol->type = SYMBOL_PARAM;
        symbol->data.parameter = param;
        symbol->is_new_context = false;

        if (param.type.key == CUSTOM) {
            symbol->var_access = ACCESS_CLASS;
        } else {
            symbol->var_access = ACCESS_PRIMITIVE;
        }

        symbol->next = table->head;
        table->head = symbol;

        return define_params(param.next, table);
    }

    return result;
}

struct analyze_result define_function(struct function_def function_def,
                                      struct table* table) {
    struct analyze_result result;
    result.status = SUCCESS;
    printf("define function: %s\n", function_def.token.val.string_v);
    if (is_declared(function_def.token.val.string_v, table)) {
        fprintf(stderr,
                error_msg[ERROR_ALREADY_DECLARED],
                function_def.token.val.string_v,
                function_def.token.line,
                function_def.token.column);
        result.status = ERROR_ALREADY_DECLARED;
        return result;
    }

    if (function_def.type.key == CUSTOM &&
        !is_type_defined(function_def.type.val.custom, table)) {
        fprintf(stderr,
                error_msg[ERROR_UNDECLARED],
                function_def.type.val.custom,
                function_def.token.line,
                function_def.token.column);
        result.status = ERROR_UNDECLARED;
        return result;
    }

    struct symbol* symbol = malloc(sizeof *symbol);
    symbol->id = function_def.token.val.string_v;
    symbol->type = SYMBOL_FUNCTION_DEF;
    symbol->data.function_def = function_def;
    symbol->is_new_context = true;
    symbol->var_access = ACCESS_FUNCTION;

    symbol->next = table->head;
    table->head = symbol;

    return define_params(function_def.params, table);
}

struct analyze_result declare_local_var(struct local_var_decl local_var,
                                        struct table* table) {
    struct analyze_result result;
    result.status = SUCCESS;
    printf("declare local var: %s\n", local_var.token.val.string_v);
    if (is_declared(local_var.token.val.string_v, table)) {
        fprintf(stderr,
                error_msg[ERROR_ALREADY_DECLARED],
                local_var.token.val.string_v,
                local_var.token.line,
                local_var.token.column);
        result.status = ERROR_ALREADY_DECLARED;
        return result;
    }

    if (local_var.type.key == CUSTOM &&
        !is_type_defined(local_var.type.val.custom, table)) {
        fprintf(stderr,
                error_msg[ERROR_UNDECLARED],
                local_var.type.val.custom,
                local_var.token.line,
                local_var.token.column);
        result.status = ERROR_UNDECLARED;
        return result;
    }

    struct symbol* symbol = malloc(sizeof *symbol);
    symbol->id = local_var.token.val.string_v;
    symbol->type = SYMBOL_LOCAL_VAR_DECL;
    symbol->data.local_var_decl = local_var;
    symbol->is_new_context = false;

    if (local_var.type.key == CUSTOM) {
        symbol->var_access = ACCESS_CLASS;
    } else {
        symbol->var_access = ACCESS_PRIMITIVE;
    }

    symbol->next = table->head;
    table->head = symbol;

    if (local_var.init != 0) {
        result = analyze_node(local_var.init, table);
        if (result.status != SUCCESS) {
            return result;
        }

        struct type type = result.type;
        result = convert_type(result.type, local_var.type);

        if (result.status != SUCCESS) {
            fprintf(stderr,
                    error_msg[result.status],
                    type.key == CUSTOM ? type.val.custom
                                       : literal_type[type.val.primitive],
                    local_var.type.key == CUSTOM
                        ? local_var.type.val.custom
                        : literal_type[local_var.type.val.primitive],
                    local_var.token.line,
                    local_var.token.column);
        }
    }
    return result;
}

struct analyze_result analyze_var(struct var var, struct table* table) {
    struct analyze_result result;
    result.status = SUCCESS;

    struct symbol* symbol = get_symbol(var.token.val.string_v, table);
    if (symbol == 0) {
        fprintf(stderr,
                error_msg[ERROR_UNDECLARED],
                var.token.val.string_v,
                var.token.line,
                var.token.column);
        result.status = ERROR_UNDECLARED;
        return result;
    }

    enum var_access var_access;
    if (var.field_access == 0) {
        if (var.array_access == 0) {
            var_access = ACCESS_PRIMITIVE;
        } else {
            var_access = ACCESS_PRIMITIVE_ARRAY;
        }
    } else {
        if (var.array_access == 0) {
            var_access = ACCESS_CLASS;
        } else {
            var_access = ACCESS_CLASS_ARRAY;
        }
    }

    result = match_access(var_access, symbol->var_access);
    if (result.status != SUCCESS) {
        fprintf(stderr,
                error_msg[result.status],
                var.token.val.string_v,
                var.token.line,
                var.token.column);
        return result;
    }

    if (var.array_access != 0) {
        result = analyze_node(var.array_access, table);
        if (result.status != SUCCESS) {
            return result;
        }

        struct type int_t;
        int_t.key = PRIMITIVE;
        int_t.val.primitive = INT;
        result = convert_type(result.type, int_t);
        if (result.status != SUCCESS) {
            fprintf(stderr,
                    error_msg[ERROR_MISMATCHED_TYPE],
                    literal_type[var.token.type],
                    literal_type[INT],
                    var.token.line,
                    var.token.column);
            return result;
        }
    }

    if (var.field_access == 0) {
        switch (symbol->type) {
            case SYMBOL_GLOBAL_VAR_DECL:
                result.type = symbol->data.global_var_decl.type;
                break;
            case SYMBOL_LOCAL_VAR_DECL:
                result.type = symbol->data.local_var_decl.type;
                break;
            case SYMBOL_PARAM:
                result.type = symbol->data.parameter.type;
            default:
                break;
        }
    } else {
        struct symbol* class = 0;
        struct node* field = 0;
        switch (symbol->type) {
            case SYMBOL_GLOBAL_VAR_DECL:
                class = get_symbol(symbol->data.global_var_decl.type.val.custom,
                                   table);
                break;
            case SYMBOL_LOCAL_VAR_DECL:
                class = get_symbol(symbol->data.local_var_decl.type.val.custom,
                                   table);
            case SYMBOL_PARAM:
                class =
                    get_symbol(symbol->data.parameter.type.val.custom, table);
                break;
            default:
                break;
        }

        field = get_field(var.field_access, class->data.class_def.field_list);
        if (field == 0) {
            fprintf(stderr,
                    error_msg[ERROR_UNDECLARED],
                    var.field_access,
                    var.token.line,
                    var.token.column);
            result.status = ERROR_UNDECLARED;
            return result;
        }

        result.type = field->val.field.type;
    }

    return result;
}

struct analyze_result analyze_return(struct return_cmd return_cmd,
                                     struct table* table) {
    struct analyze_result result;
    result.status = SUCCESS;

    result = analyze_node(return_cmd.exp, table);
    if (result.status != SUCCESS) {
        return result;
    }

    struct symbol* function = get_self_function(table);
    if (result.type.key == function->data.function_def.type.key) {
        if (result.type.key == CUSTOM &&
            strcmp(result.type.val.custom,
                   function->data.function_def.type.val.custom) == 0) {
            return result;
        }
    }

    fprintf(stderr,
            error_msg[ERROR_MISMATCHED_TYPE_RETURN],
            function->data.function_def.token.val.string_v,
            function->data.function_def.token.line,
            function->data.function_def.token.column);
    result.status = ERROR_MISMATCHED_TYPE_RETURN;

    return result;
}

struct analyze_result analyze_attr(struct attr_cmd attr_cmd,
                                   struct table* table) {
    struct analyze_result var = analyze_node(attr_cmd.var, table);
    if (var.status != SUCCESS) {
        return var;
    }
    struct analyze_result exp = analyze_node(attr_cmd.exp, table);
    if (exp.status != SUCCESS) {
        return exp;
    }
    struct analyze_result result = convert_type(exp.type, var.type);
    if (result.status != SUCCESS) {
        fprintf(stderr,
                error_msg[result.status],
                exp.type.key == CUSTOM ? exp.type.val.custom
                                       : literal_type[exp.type.val.primitive],
                var.type.key == CUSTOM ? var.type.val.custom
                                       : literal_type[var.type.val.primitive],
                attr_cmd.var->val.var.token.line,
                attr_cmd.var->val.var.token.column);
    }

    return result;
}

struct analyze_result analyze_shift(struct shift_cmd shift_cmd,
                                    struct table* table) {
    struct analyze_result var = analyze_node(shift_cmd.var, table);
    if (var.status != SUCCESS) {
        return var;
    }
    struct analyze_result exp = analyze_node(shift_cmd.exp, table);
    if (exp.status != SUCCESS) {
        return exp;
    }
    struct analyze_result result = convert_type(exp.type, val_type[INT]);
    if (result.status != SUCCESS) {
        fprintf(stderr,
                error_msg[result.status],
                exp.type.key == CUSTOM ? exp.type.val.custom
                                       : literal_type[exp.type.val.primitive],
                val_type[INT].key == CUSTOM
                    ? val_type[INT].val.custom
                    : literal_type[val_type[INT].val.primitive],
                shift_cmd.var->val.var.token.line,
                shift_cmd.var->val.var.token.column);
        return result;
    }

    result = convert_type(val_type[INT], var.type);
    if (result.status != SUCCESS) {
        fprintf(stderr,
                error_msg[result.status],
                literal_type[INT],
                var.type.key == CUSTOM ? var.type.val.custom
                                       : literal_type[var.type.val.primitive],
                shift_cmd.var->val.var.token.line,
                shift_cmd.var->val.var.token.column);
    }
    return result;
}

struct analyze_result analyze_for(struct for_cmd for_cmd, struct table* table) {
    struct analyze_result result;
    result.status = SUCCESS;

    result = analyze_node(for_cmd.initialization, table);
    if (result.status != SUCCESS) {
        return result;
    }

    struct analyze_result cond = analyze_node(for_cmd.condition, table);
    if (result.status != SUCCESS) {
        return cond;
    }

    result = convert_type(cond.type, val_type[BOOL]);
    if (result.status != SUCCESS) {
        fprintf(stderr,
                error_msg[result.status],
                cond.type.key == CUSTOM ? cond.type.val.custom
                                        : literal_type[cond.type.val.primitive],
                literal_type[BOOL],
                0,
                0);
        return result;
    }

    result = analyze_node(for_cmd.update, table);
    if (result.status != SUCCESS) {
        return result;
    }

    result = analyze_node(for_cmd.cmd_block, table);
    if (result.status != SUCCESS) {
        return result;
    }

    return result;
}

struct analyze_result analyze_function(struct function_cmd function_cmd,
                                       struct table* table) {
    struct analyze_result result;
    result.status = SUCCESS;

    struct symbol* function =
        get_symbol(function_cmd.token.val.string_v, table);
    if (function == 0) {
        fprintf(stderr,
                error_msg[ERROR_UNDECLARED],
                function_cmd.token.val.string_v,
                function_cmd.token.line,
                function_cmd.token.column);
        result.status = ERROR_UNDECLARED;
    }

    result = match_access(ACCESS_FUNCTION, function->var_access);
    if (result.status != SUCCESS) {
        fprintf(stderr,
                error_msg[result.status],
                function_cmd.token.val.string_v,
                function_cmd.token.line,
                function_cmd.token.column);
        return result;
    }

    struct node* params_list = function->data.function_def.params;
    struct node* arg_list = function_cmd.arg_list;
    struct parameter parameter;

    while (params_list != 0) {
        parameter = params_list->val.parameter;

        if (arg_list == 0) {
            fprintf(stderr,
                    error_msg[ERROR_MISSING_ARGS],
                    function_cmd.token.val.string_v,
                    function_cmd.token.line,
                    function_cmd.token.column);
            result.status = ERROR_MISSING_ARGS;
            return result;
        }

        if (arg_list->val.arg_list.arg->type != N_DOT_ARG) {
            struct analyze_result arg_result =
                analyze_node(arg_list->val.arg_list.arg, table);
            if (arg_result.status != SUCCESS) {
                return result;
            }

            result = convert_type(arg_result.type, parameter.type);
            if (result.status != SUCCESS) {
                return result;
            }
        }

        params_list = params_list->val.parameter.next;
        arg_list = arg_list->val.arg_list.next;
    }

    if (arg_list != 0) {
        fprintf(stderr,
                error_msg[ERROR_TOO_MANY_ARGS],
                function_cmd.token.val.string_v,
                function_cmd.token.line,
                function_cmd.token.column);
        result.status = ERROR_TOO_MANY_ARGS;
        return result;
    }

    result.type = function->data.function_def.type;
    return result;
}

struct analyze_result analyze_binary(struct binary_exp binary_exp,
                                     struct table* table) {
    struct analyze_result result;
    result.status = SUCCESS;

    struct analyze_result left = analyze_node(binary_exp.left, table);
    if (left.status != SUCCESS) {
        return left;
    }

    struct analyze_result right = analyze_node(binary_exp.right, table);
    if (right.status != SUCCESS) {
        return right;
    }

    result = infer_type(left.type, right.type);
    if (result.status != SUCCESS) {
        fprintf(stderr,
                error_msg[ERROR_MISMATCHED_TYPE],
                left.type.key == CUSTOM ? left.type.val.custom
                                        : literal_type[left.type.val.primitive],
                right.type.key == CUSTOM
                    ? right.type.val.custom
                    : literal_type[right.type.val.primitive],
                0,
                0);
    }

    return result;
}

struct analyze_result analyze_ternary(struct ternary_exp ternary_exp,
                                      struct table* table) {
    struct analyze_result result;
    result.status = SUCCESS;

    result = analyze_node(ternary_exp.condition, table);
    if (result.status != SUCCESS) {
        return result;
    }

    result = convert_type(result.type, val_type[BOOL]);
    if (result.status != SUCCESS) {
        fprintf(stderr,
                error_msg[result.status],
                result.type.key == CUSTOM
                    ? result.type.val.custom
                    : literal_type[result.type.val.primitive],
                literal_type[BOOL],
                0,
                0);
        return result;
    }

    struct analyze_result exp = analyze_node(ternary_exp.exp1, table);
    if (exp.status != SUCCESS) {
        return exp;
    }

    result = analyze_node(ternary_exp.exp2, table);
    if (result.status != SUCCESS) {
        return result;
    }

    if (exp.type.key == result.type.key) {
        if (exp.type.key == CUSTOM &&
            strcmp(exp.type.val.custom, result.type.val.custom) == 0) {
            return result;
        } else if (exp.type.key == PRIMITIVE &&
                   exp.type.val.primitive == result.type.val.primitive) {
            return result;
        }
    }

    fprintf(stderr,
            error_msg[ERROR_MISMATCHED_TYPE],
            result.type.key == CUSTOM ? result.type.val.custom
                                      : literal_type[result.type.val.primitive],
            result.type.key == CUSTOM ? result.type.val.custom
                                      : literal_type[result.type.val.primitive],
            0,
            0);
    return result;
}

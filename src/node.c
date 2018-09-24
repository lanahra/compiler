#include <stdio.h>
#include <stdlib.h>
#include "../include/parser.tab.h"

struct node* alloc_node(enum node_type type) {
    struct node* node = malloc(sizeof *node);
    node->type = type;
    return node;
}

struct node* make_int_literal(int int_v) {
    struct node* node = alloc_node(N_INT_LITERAL);
    node->val.literal.int_v = int_v;
    return node;
}

struct node* make_float_literal(float float_v) {
    struct node* node = alloc_node(N_FLOAT_LITERAL);
    node->val.literal.float_v = float_v;
    return node;
}

struct node* make_bool_literal(bool bool_v) {
    struct node* node = alloc_node(N_BOOL_LITERAL);
    node->val.literal.bool_v = bool_v;
    return node;
}

struct node* make_char_literal(char char_v) {
    struct node* node = alloc_node(N_CHAR_LITERAL);
    node->val.literal.char_v = char_v;
    return node;
}

struct node* make_string_literal(char* string_v) {
    struct node* node = alloc_node(N_STRING_LITERAL);
    node->val.literal.string_v = string_v;
    return node;
}

struct node* make_unary_exp(int op, struct node* operand) {
    struct node* node = alloc_node(N_UNARY_EXP);
    node->val.unary_exp.op = op;
    node->val.unary_exp.operand = operand;
    return node;
}

struct node* make_binary_exp(struct node* left, int op, struct node* right) {
    struct node* node = alloc_node(N_BINARY_EXP);
    node->val.binary_exp.left = left;
    node->val.binary_exp.op = op;
    node->val.binary_exp.right = right;
    return node;
}

struct node* make_ternary_exp(struct node* condition,
                              struct node* exp1,
                              struct node* exp2) {
    struct node* node = alloc_node(N_TERNARY_EXP);
    node->val.ternary_exp.condition = condition;
    node->val.ternary_exp.exp1 = exp1;
    node->val.ternary_exp.exp2 = exp2;
    return node;
}

struct node* make_exp_list(struct node* exp_list, struct node* exp) {
    struct node* node = alloc_node(N_EXP_LIST);
    node->val.exp_list.exp_list = exp_list;
    node->val.exp_list.exp = exp;
    return node;
}

struct node* make_switch_cmd(struct node* control_exp, struct node* cmd_block) {
    struct node* node = alloc_node(N_SWITCH);
    node->val.switch_cmd.control_exp = control_exp;
    node->val.switch_cmd.cmd_block = cmd_block;
    return node;
}

struct node* make_do_while_cmd(struct node* cmd_block, struct node* condition) {
    struct node* node = alloc_node(N_DO_WHILE);
    node->val.do_while_cmd.cmd_block = cmd_block;
    node->val.do_while_cmd.condition = condition;
    return node;
}

struct node* make_while_cmd(struct node* condition, struct node* cmd_block) {
    struct node* node = alloc_node(N_WHILE);
    node->val.while_cmd.condition = condition;
    node->val.while_cmd.cmd_block = cmd_block;
    return node;
}

struct node* make_for_cmd(struct node* initialization,
                          struct node* condition,
                          struct node* update,
                          struct node* cmd_block) {
    struct node* node = alloc_node(N_FOR);
    node->val.for_cmd.initialization = initialization;
    node->val.for_cmd.condition = condition;
    node->val.for_cmd.update = update;
    node->val.for_cmd.cmd_block = cmd_block;
    return node;
}

struct node* make_foreach_cmd(char* item,
                              struct node* exp_list,
                              struct node* cmd_block) {
    struct node* node = alloc_node(N_FOREACH);
    node->val.foreach_cmd.item = item;
    node->val.foreach_cmd.exp_list = exp_list;
    node->val.foreach_cmd.cmd_block = cmd_block;
    return node;
}

struct node* make_dot_arg() {
    struct node* node = alloc_node(N_DOT_ARG);
    return node;
}

struct node* make_arg_list(struct node* arg_list, struct node* arg) {
    struct node* node = alloc_node(N_ARG_LIST);
    node->val.arg_list.arg_list = arg_list;
    node->val.arg_list.arg = arg;
    return node;
}

struct node* make_function_cmd(char* name, struct node* arg_list) {
    struct node* node = alloc_node(N_FUNCTION);
    node->val.function_cmd.name = name;
    node->val.function_cmd.arg_list = arg_list;
    return node;
}

struct node* make_pipe_cmd(struct node* pipe_cmd,
                           int pipe_op,
                           struct node* function_cmd) {
    struct node* node = alloc_node(N_PIPE);
    node->val.pipe_cmd.pipe_cmd = pipe_cmd;
    node->val.pipe_cmd.pipe_op = pipe_op;
    node->val.pipe_cmd.function_cmd = function_cmd;
    return node;
}

struct node* make_if_cmd(struct node* condition,
                         struct node* then_cmd_block,
                         struct node* else_cmd_block) {
    struct node* node = alloc_node(N_IF);
    node->val.if_cmd.condition = condition;
    node->val.if_cmd.then_cmd_block = then_cmd_block;
    node->val.if_cmd.else_cmd_block = else_cmd_block;
    return node;
}

struct node* make_out_cmd(struct node* exp_list) {
    struct node* node = alloc_node(N_OUTPUT);
    node->val.out_cmd.exp_list = exp_list;
    return node;
}

struct node* make_in_cmd(struct node* exp) {
    struct node* node = alloc_node(N_INPUT);
    node->val.in_cmd.exp = exp;
    return node;
}

struct node* make_case_label(int case_val) {
    struct node* node = alloc_node(N_CASE);
    node->val.case_label.case_val = case_val;
    return node;
}

struct node* make_return_cmd(struct node* exp) {
    struct node* node = alloc_node(N_RETURN);
    node->val.return_cmd.exp = exp;
    return node;
}

struct node* make_shift_cmd(struct node* var, int shift_op, struct node* exp) {
    struct node* node = alloc_node(N_SHIFT);
    node->val.shift_cmd.var = var;
    node->val.shift_cmd.shift_op = shift_op;
    node->val.shift_cmd.exp = exp;
    return node;
}

struct node* make_break_cmd() {
    struct node* node = alloc_node(N_BREAK);
    return node;
}

struct node* make_continue_cmd() {
    struct node* node = alloc_node(N_CONTINUE);
    return node;
}

struct node* make_var(char* name,
                      char* field_access,
                      struct node* array_access) {
    struct node* node = alloc_node(N_VAR);
    node->val.var.name = name;
    node->val.var.field_access = field_access;
    node->val.var.array_access = array_access;
    return node;
}

struct node* make_attr_cmd(struct node* var, struct node* exp) {
    struct node* node = alloc_node(N_ATTRIBUTION);
    node->val.attr_cmd.var = var;
    node->val.attr_cmd.exp = exp;
    return node;
}

struct node* make_class_var_decl(char* type, char* name) {
    struct node* node = alloc_node(N_LOCAL_VAR_DECL);
    node->val.local_var_decl.is_static = false;
    node->val.local_var_decl.is_const = false;
    node->val.local_var_decl.type.key = CUSTOM;
    node->val.local_var_decl.type.val.custom = type;
    node->val.local_var_decl.name = name;
    node->val.local_var_decl.init = 0;
    return node;
}

struct node* make_var_decl(int type, char* name, struct node* init) {
    struct node* node = alloc_node(N_LOCAL_VAR_DECL);
    node->val.local_var_decl.is_static = false;
    node->val.local_var_decl.is_const = false;
    node->val.local_var_decl.type.key = PRIMITIVE;
    node->val.local_var_decl.type.val.primitive = type;
    node->val.local_var_decl.name = name;
    node->val.local_var_decl.init = init;
    return node;
}

struct node* add_decl_modifier(bool is_static,
                               bool is_const,
                               struct node* decl) {
    decl->val.local_var_decl.is_static = is_static;
    decl->val.local_var_decl.is_const = is_const;
    return decl;
}

struct node* make_cmd_list(struct node* cmd_list, struct node* cmd) {
    struct node* node = alloc_node(N_CMD_LIST);
    node->val.cmd_list.cmd_list = cmd_list;
    node->val.cmd_list.cmd = cmd;
    return node;
}

struct node* make_high_list(struct node* high_list, struct node* cmd) {
    struct node* node = alloc_node(N_HIGH_LIST);
    node->val.high_list.high_list = high_list;
    node->val.high_list.cmd = cmd;
    return node;
}

struct node* make_cmd_block(struct node* high_list) {
    struct node* node = alloc_node(N_CMD_BLOCK);
    node->val.cmd_block.high_list = high_list;
    return node;
}

struct type make_primitive(int type) {
    struct type type_t;
    type_t.key = PRIMITIVE;
    type_t.val.primitive = type;
    return type_t;
}

struct type make_custom(char* type) {
    struct type type_t;
    type_t.key = CUSTOM;
    type_t.val.custom = type;
    return type_t;
}

struct node* make_parameter(bool is_const, struct type type, char* name) {
    struct node* node = alloc_node(N_PARAM);
    node->val.parameter.is_const = is_const;
    node->val.parameter.type = type;
    node->val.parameter.name = name;
    return node;
}

struct node* make_param_list(struct node* param_list, struct node* param) {
    struct node* node = alloc_node(N_PARAM_LIST);
    node->val.param_list.param_list = param_list;
    node->val.param_list.param = param;
    return node;
}

struct node* make_function_def(bool is_static,
                               struct type type,
                               char* name,
                               struct node* params,
                               struct node* cmd_block) {
    struct node* node = alloc_node(N_FUNCTION_DEF);
    node->val.function_def.is_static = is_static;
    node->val.function_def.type = type;
    node->val.function_def.name = name;
    node->val.function_def.params = params;
    node->val.function_def.cmd_block = cmd_block;
    return node;
}

struct node* make_field(enum access_modifier access,
                        struct type type,
                        char* name) {
    struct node* node = alloc_node(N_FIELD);
    node->val.field.access = access;
    node->val.field.type = type;
    node->val.field.name = name;
    return node;
}

struct node* make_field_list(struct node* field_list, struct node* field) {
    struct node* node = alloc_node(N_FIELD_LIST);
    node->val.field_list.field_list = field_list;
    node->val.field_list.field = field;
    return node;
}

struct node* make_class_def(char* name, struct node* field_list) {
    struct node* node = alloc_node(N_CLASS_DEF);
    node->val.class_def.name = name;
    node->val.class_def.field_list = field_list;
    return node;
}

struct node* make_global_var_decl(char* name,
                                  int size,
                                  bool is_static,
                                  struct type type) {
    struct node* node = alloc_node(N_GLOBAL_VAR_DECL);
    node->val.global_var_decl.name = name;
    node->val.global_var_decl.size = size;
    node->val.global_var_decl.is_static = is_static;
    node->val.global_var_decl.type = type;
    return node;
};

struct node* make_unit(struct node* unit, struct node* element) {
    struct node* node = alloc_node(N_UNIT);
    node->val.unit.unit = unit;
    node->val.unit.element = element;
    return node;
}

void free_node(struct node* node) {
    if (node != 0) {
        switch (node->type) {
            case N_STRING_LITERAL:
                free(node->val.literal.string_v);
                break;
            case N_UNARY_EXP:
                free_node(node->val.unary_exp.operand);
                break;
            case N_BINARY_EXP:
                free_node(node->val.binary_exp.left);
                free_node(node->val.binary_exp.right);
                break;
            case N_TERNARY_EXP:
                free_node(node->val.ternary_exp.condition);
                free_node(node->val.ternary_exp.exp1);
                free_node(node->val.ternary_exp.exp2);
                break;
            case N_EXP_LIST:
                free_node(node->val.exp_list.exp_list);
                free_node(node->val.exp_list.exp);
                break;
            case N_SWITCH:
                free_node(node->val.switch_cmd.control_exp);
                free_node(node->val.switch_cmd.cmd_block);
                break;
            case N_DO_WHILE:
                free_node(node->val.do_while_cmd.cmd_block);
                free_node(node->val.do_while_cmd.condition);
                break;
            case N_WHILE:
                free_node(node->val.while_cmd.condition);
                free_node(node->val.while_cmd.cmd_block);
                break;
            case N_FOR:
                free_node(node->val.for_cmd.initialization);
                free_node(node->val.for_cmd.condition);
                free_node(node->val.for_cmd.update);
                free_node(node->val.for_cmd.cmd_block);
                break;
            case N_FOREACH:
                free(node->val.foreach_cmd.item);
                free_node(node->val.foreach_cmd.exp_list);
                free_node(node->val.foreach_cmd.cmd_block);
                break;
            case N_ARG_LIST:
                free_node(node->val.arg_list.arg_list);
                free_node(node->val.arg_list.arg);
                break;
            case N_FUNCTION:
                free(node->val.function_cmd.name);
                free_node(node->val.function_cmd.arg_list);
                break;
            case N_PIPE:
                free_node(node->val.pipe_cmd.pipe_cmd);
                free_node(node->val.pipe_cmd.function_cmd);
                break;
            case N_IF:
                free_node(node->val.if_cmd.condition);
                free_node(node->val.if_cmd.then_cmd_block);
                free_node(node->val.if_cmd.else_cmd_block);
                break;
            case N_OUTPUT:
                free_node(node->val.out_cmd.exp_list);
                break;
            case N_INPUT:
                free_node(node->val.in_cmd.exp);
                break;
            case N_RETURN:
                free_node(node->val.return_cmd.exp);
                break;
            case N_SHIFT:
                free_node(node->val.shift_cmd.var);
                free_node(node->val.shift_cmd.exp);
                break;
            case N_VAR:
                free(node->val.var.name);
                free(node->val.var.field_access);
                free_node(node->val.var.array_access);
                break;
            case N_ATTRIBUTION:
                free_node(node->val.attr_cmd.var);
                free_node(node->val.attr_cmd.exp);
                break;
            case N_LOCAL_VAR_DECL:
                if (node->val.local_var_decl.type.key == CUSTOM) {
                    free(node->val.local_var_decl.type.val.custom);
                };
                free(node->val.local_var_decl.name);
                free_node(node->val.local_var_decl.init);
                break;
            case N_CMD_LIST:
                free_node(node->val.cmd_list.cmd_list);
                free_node(node->val.cmd_list.cmd);
                break;
            case N_HIGH_LIST:
                free_node(node->val.high_list.high_list);
                free_node(node->val.high_list.cmd);
                break;
            case N_CMD_BLOCK:
                free_node(node->val.cmd_block.high_list);
                break;
            case N_PARAM:
                if (node->val.parameter.type.key == CUSTOM) {
                    free(node->val.parameter.type.val.custom);
                };
                free(node->val.parameter.name);
                break;
            case N_PARAM_LIST:
                free_node(node->val.param_list.param_list);
                free_node(node->val.param_list.param);
                break;
            case N_FUNCTION_DEF:
                if (node->val.function_def.type.key == CUSTOM) {
                    free(node->val.function_def.type.val.custom);
                };
                free(node->val.function_def.name);
                free_node(node->val.function_def.params);
                free_node(node->val.function_def.cmd_block);
                break;
            case N_FIELD:
                if (node->val.field.type.key == CUSTOM) {
                    free(node->val.field.type.val.custom);
                };
                free(node->val.field.name);
                break;
            case N_FIELD_LIST:
                free_node(node->val.field_list.field_list);
                free_node(node->val.field_list.field);
                break;
            case N_CLASS_DEF:
                free(node->val.class_def.name);
                free_node(node->val.class_def.field_list);
                break;
            case N_GLOBAL_VAR_DECL:
                free(node->val.global_var_decl.name);

                if (node->val.global_var_decl.type.key == CUSTOM) {
                    free(node->val.global_var_decl.type.val.custom);
                };

                break;
            case N_UNIT:
                free_node(node->val.unit.unit);
                free_node(node->val.unit.element);
                break;
            default:
                break;
        }

        free(node);
    }
}

static void decompile_type(struct type type) {
    if (type.key == PRIMITIVE) {
        switch (type.val.primitive) {
            case INT:
                printf("int");
                break;
            case FLOAT:
                printf("float");
                break;
            case BOOL:
                printf("bool");
                break;
            case CHAR:
                printf("char");
                break;
            case STRING:
                printf("string");
                break;
            default:
                break;
        }
    } else {
        printf("%s", type.val.custom);
    }
}

void decompile_node(struct node* node) {
    static bool is_case_cmd = false;
    if (node != 0) {
        switch (node->type) {
            case N_INT_LITERAL:
                printf("%d", node->val.literal.int_v);
                break;
            case N_FLOAT_LITERAL:
                printf("%f", node->val.literal.float_v);
                break;
            case N_CHAR_LITERAL:
                printf("%c", node->val.literal.char_v);
                break;
            case N_STRING_LITERAL:
                printf("%s", node->val.literal.string_v);
                break;
            case N_BOOL_LITERAL:
                printf(node->val.literal.bool_v ? "true" : "false");
                break;
            case N_UNARY_EXP:
                printf("%c", node->val.unary_exp.op);
                decompile_node(node->val.unary_exp.operand);
                break;
            case N_BINARY_EXP:
                decompile_node(node->val.binary_exp.left);

                switch (node->val.binary_exp.op) {
                    case FORWARD_PIPE:
                        printf(" %%>%% ");
                        break;
                    case BASH_PIPE:
                        printf(" %%|%% ");
                        break;
                    case OR_OP:
                        printf(" || ");
                        break;
                    case AND_OP:
                        printf(" && ");
                        break;
                    case EQ_OP:
                        printf(" == ");
                        break;
                    case NE_OP:
                        printf(" != ");
                        break;
                    case LE_OP:
                        printf(" <= ");
                        break;
                    case GE_OP:
                        printf(" >= ");
                        break;
                    default:
                        printf(" %c ", node->val.binary_exp.op);
                }

                decompile_node(node->val.binary_exp.right);
                break;
            case N_TERNARY_EXP:
                decompile_node(node->val.ternary_exp.condition);
                printf(" ? ");
                decompile_node(node->val.ternary_exp.exp1);
                printf(" : ");
                decompile_node(node->val.ternary_exp.exp2);
                break;
            case N_EXP_LIST:
                decompile_node(node->val.exp_list.exp_list);
                printf(", ");
                decompile_node(node->val.exp_list.exp);
                break;
            case N_SWITCH:
                printf("switch (");
                decompile_node(node->val.switch_cmd.control_exp);
                printf(") ");

                if (node->val.switch_cmd.cmd_block != 0) {
                    decompile_node(node->val.switch_cmd.cmd_block);
                }
                break;
            case N_DO_WHILE:
                printf("do ");

                if (node->val.do_while_cmd.cmd_block != 0) {
                    decompile_node(node->val.do_while_cmd.cmd_block);
                }

                printf(" while (");
                decompile_node(node->val.do_while_cmd.condition);
                printf(")");
                break;
            case N_WHILE:
                printf("while (");
                decompile_node(node->val.while_cmd.condition);
                printf(") do ");

                if (node->val.while_cmd.cmd_block != 0) {
                    decompile_node(node->val.while_cmd.cmd_block);
                }
                break;
            case N_FOR:
                printf("for (");
                decompile_node(node->val.for_cmd.initialization);
                printf(" : ");
                decompile_node(node->val.for_cmd.condition);
                printf(" : ");
                decompile_node(node->val.for_cmd.update);
                printf(") ");

                if (node->val.for_cmd.cmd_block != 0) {
                    decompile_node(node->val.for_cmd.cmd_block);
                }
                break;
            case N_FOREACH:
                printf("foreach (%s : ", node->val.foreach_cmd.item);
                decompile_node(node->val.foreach_cmd.exp_list);
                printf(") ");

                if (node->val.foreach_cmd.cmd_block != 0) {
                    decompile_node(node->val.foreach_cmd.cmd_block);
                }
                break;
            case N_DOT_ARG:
                printf(".");
                break;
            case N_ARG_LIST:
                decompile_node(node->val.arg_list.arg_list);
                printf(", ");
                decompile_node(node->val.arg_list.arg);
                break;
            case N_FUNCTION:
                printf("%s(", node->val.function_cmd.name);
                decompile_node(node->val.function_cmd.arg_list);
                printf(")");
                break;
            case N_PIPE:
                decompile_node(node->val.pipe_cmd.pipe_cmd);

                switch (node->val.pipe_cmd.pipe_op) {
                    case FORWARD_PIPE:
                        printf(" %%>%% ");
                        break;
                    case BASH_PIPE:
                        printf(" %%|%% ");
                        break;
                }

                decompile_node(node->val.pipe_cmd.function_cmd);
                break;
            case N_IF:
                printf("if (");
                decompile_node(node->val.if_cmd.condition);
                printf(") then ");

                if (node->val.if_cmd.then_cmd_block != 0) {
                    decompile_node(node->val.if_cmd.then_cmd_block);
                }

                if (node->val.if_cmd.else_cmd_block != 0) {
                    printf("else ");
                    decompile_node(node->val.if_cmd.else_cmd_block);
                }

                break;
            case N_OUTPUT:
                printf("output ");
                decompile_node(node->val.out_cmd.exp_list);
                break;
            case N_INPUT:
                printf("input ");
                decompile_node(node->val.in_cmd.exp);
                break;
            case N_CASE:
                is_case_cmd = true;
                printf("case %d:", node->val.case_label.case_val);
                break;
            case N_RETURN:
                printf("return ");
                decompile_node(node->val.return_cmd.exp);
                break;
            case N_SHIFT:
                decompile_node(node->val.shift_cmd.var);

                switch (node->val.shift_cmd.shift_op) {
                    case SL_OP:
                        printf(" << ");
                        break;
                    case SR_OP:
                        printf(" >> ");
                        break;
                }

                decompile_node(node->val.shift_cmd.exp);
                break;
            case N_BREAK:
                printf("break");
                break;
            case N_CONTINUE:
                printf("continue");
                break;
            case N_VAR:
                printf("%s", node->val.var.name);

                if (node->val.var.array_access) {
                    printf("[");
                    decompile_node(node->val.var.array_access);
                    printf("]");
                }

                if (node->val.var.field_access) {
                    printf("$%s", node->val.var.field_access);
                }

                break;
            case N_ATTRIBUTION:
                decompile_node(node->val.attr_cmd.var);
                printf(" = ");
                decompile_node(node->val.attr_cmd.exp);
                break;
            case N_LOCAL_VAR_DECL:
                if (node->val.local_var_decl.is_static) {
                    printf("static ");
                }

                if (node->val.local_var_decl.is_const) {
                    printf("const ");
                }

                decompile_type(node->val.local_var_decl.type);
                printf(" %s", node->val.local_var_decl.name);

                if (node->val.local_var_decl.init != 0) {
                    printf(" <= ");
                    decompile_node(node->val.local_var_decl.init);
                }
                break;
            case N_CMD_LIST:
                decompile_node(node->val.cmd_list.cmd_list);
                printf(", ");
                decompile_node(node->val.cmd_list.cmd);
                break;
            case N_HIGH_LIST:
                decompile_node(node->val.high_list.high_list);
                printf(is_case_cmd ? "\n" : ";\n");
                is_case_cmd = false;
                decompile_node(node->val.high_list.cmd);
                break;
            case N_CMD_BLOCK:
                printf("{\n");

                if (node->val.cmd_block.high_list != 0) {
                    decompile_node(node->val.cmd_block.high_list);
                    printf(is_case_cmd ? "\n" : ";\n");
                    is_case_cmd = false;
                }

                printf("}\n");
                break;
            case N_PARAM:
                if (node->val.parameter.is_const) {
                    printf("const ");
                }

                decompile_type(node->val.parameter.type);
                printf(" %s", node->val.parameter.name);
                break;
            case N_PARAM_LIST:
                decompile_node(node->val.param_list.param_list);
                printf(", ");
                decompile_node(node->val.param_list.param);
                break;
            case N_FUNCTION_DEF:
                if (node->val.function_def.is_static) {
                    printf("static ");
                }

                decompile_type(node->val.function_def.type);
                printf(" %s (", node->val.function_def.name);
                decompile_node(node->val.function_def.params);
                printf(") ");

                if (node->val.function_def.cmd_block != 0) {
                    decompile_node(node->val.function_def.cmd_block);
                }
                break;
            case N_FIELD:
                switch (node->val.field.access) {
                    case PRIV:
                        printf("private ");
                        break;
                    case PUB:
                        printf("public ");
                        break;
                    case PROT:
                        printf("protected ");
                        break;
                    default:
                        break;
                }

                decompile_type(node->val.field.type);
                printf(" %s", node->val.field.name);
                break;
            case N_FIELD_LIST:
                decompile_node(node->val.field_list.field_list);
                printf(" : ");
                decompile_node(node->val.field_list.field);
                break;
            case N_CLASS_DEF:
                printf("class %s[ ", node->val.class_def.name);
                decompile_node(node->val.class_def.field_list);
                printf(" ];\n");
                break;
            case N_GLOBAL_VAR_DECL:
                printf("%s", node->val.global_var_decl.name);

                if (node->val.global_var_decl.size >= 0) {
                    printf("[%d]", node->val.global_var_decl.size);
                }

                if (node->val.global_var_decl.is_static) {
                    printf(" static");
                }

                printf(" ");
                decompile_type(node->val.global_var_decl.type);
                printf(";\n");
                break;
            case N_UNIT:
                decompile_node(node->val.unit.unit);
                printf("\n");
                decompile_node(node->val.unit.element);
                break;
            default:
                break;
        }
    }
}

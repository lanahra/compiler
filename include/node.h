#ifndef NODE_H
#define NODE_H
#include <stdbool.h>

enum node_type {
    N_INT_LITERAL,
    N_FLOAT_LITERAL,
    N_CHAR_LITERAL,
    N_STRING_LITERAL,
    N_BOOL_LITERAL,
    N_UNARY_EXP,
    N_BINARY_EXP,
    N_TERNARY_EXP,
    N_EXP_LIST,
    N_SWITCH,
    N_DO_WHILE,
    N_WHILE,
    N_FOR,
    N_FOREACH,
    N_DOT_ARG,
    N_ARG_LIST,
    N_FUNCTION,
    N_PIPE,
    N_IF,
    N_OUTPUT,
    N_INPUT,
    N_CASE,
    N_RETURN,
    N_SHIFT,
    N_BREAK,
    N_CONTINUE,
    N_VAR,
    N_ATTRIBUTION,
    N_LOCAL_VAR_DECL,
    N_CMD_LIST,
    N_CMD_BLOCK,
    N_HIGH_LIST,
    N_PARAM,
    N_FUNCTION_DEF,
    N_FIELD,
    N_CLASS_DEF,
    N_GLOBAL_VAR_DECL,
    N_UNIT
};

extern const char* type_name[];

union literal {
    int int_v;
    float float_v;
    char char_v;
    char* string_v;
    bool bool_v;
};

struct token {
    int line;
    int column;
    int type;
    union literal val;
};

struct unary_exp {
    int op;
    struct node* operand;
};

struct binary_exp {
    struct node* left;
    int op;
    struct node* right;
};

struct ternary_exp {
    struct node* condition;
    struct node* exp1;
    struct node* exp2;
};

struct exp_list {
    struct node* exp_list;
    struct node* exp;
};

struct switch_cmd {
    struct node* control_exp;
    struct node* cmd_block;
};

struct do_while_cmd {
    struct node* cmd_block;
    struct node* condition;
};

struct while_cmd {
    struct node* condition;
    struct node* cmd_block;
};

struct for_cmd {
    struct node* initialization;
    struct node* condition;
    struct node* update;
    struct node* cmd_block;
};

struct foreach_cmd {
    char* item;
    struct node* exp_list;
    struct node* cmd_block;
};

struct arg_list {
    struct node* arg_list;
    struct node* arg;
};

struct function_cmd {
    struct token token;
    struct node* arg_list;
};

struct pipe_cmd {
    struct node* pipe_cmd;
    int pipe_op;
    struct node* function_cmd;
};

struct if_cmd {
    struct node* condition;
    struct node* then_cmd_block;
    struct node* else_cmd_block;
};

struct out_cmd {
    struct node* exp_list;
};

struct in_cmd {
    struct node* exp;
};

struct case_label {
    int case_val;
};

struct return_cmd {
    struct node* exp;
};

struct shift_cmd {
    struct node* var;
    int shift_op;
    struct node* exp;
};

struct var {
    struct token token;
    char* field_access;
    struct node* array_access;
};

struct attr_cmd {
    struct node* var;
    struct node* exp;
};

enum type_key { PRIMITIVE, CUSTOM };

struct type {
    enum type_key key;
    union val {
        int primitive;
        char* custom;
    } val;
};

struct local_var_decl {
    bool is_static;
    bool is_const;
    struct type type;
    struct token token;
    struct node* init;
};

struct cmd_list {
    struct node* cmd_list;
    struct node* cmd;
};

struct high_list {
    struct node* high_list;
    struct node* cmd;
};

struct cmd_block {
    struct node* high_list;
};

struct parameter {
    bool is_const;
    struct type type;
    struct token token;
    struct node* next;
};

struct function_def {
    bool is_static;
    struct type type;
    struct token token;
    struct node* params;
    struct node* cmd_block;
};

enum access_modifier { NONE, PRIV, PUB, PROT };

struct field {
    enum access_modifier access;
    struct type type;
    struct token token;
    struct node* next;
};

struct class_def {
    struct token token;
    struct node* field_list;
};

struct global_var_decl {
    struct token token;
    int size;
    bool is_static;
    struct type type;
};

struct unit {
    struct node* unit;
    struct node* element;
};

union node_value {
    union literal literal;
    struct unary_exp unary_exp;
    struct binary_exp binary_exp;
    struct ternary_exp ternary_exp;
    struct exp_list exp_list;
    struct switch_cmd switch_cmd;
    struct do_while_cmd do_while_cmd;
    struct while_cmd while_cmd;
    struct for_cmd for_cmd;
    struct foreach_cmd foreach_cmd;
    struct arg_list arg_list;
    struct function_cmd function_cmd;
    struct pipe_cmd pipe_cmd;
    struct if_cmd if_cmd;
    struct out_cmd out_cmd;
    struct in_cmd in_cmd;
    struct case_label case_label;
    struct return_cmd return_cmd;
    struct shift_cmd shift_cmd;
    struct var var;
    struct attr_cmd attr_cmd;
    struct local_var_decl local_var_decl;
    struct cmd_list cmd_list;
    struct high_list high_list;
    struct cmd_block cmd_block;
    struct parameter parameter;
    struct function_def function_def;
    struct field field;
    struct class_def class_def;
    struct global_var_decl global_var_decl;
    struct unit unit;
};

struct node {
    enum node_type type;
    union node_value val;
};

struct node* alloc_node(enum node_type);
struct node* make_int_literal(int int_v);
struct node* make_float_literal(float float_v);
struct node* make_bool_literal(bool bool_v);
struct node* make_char_literal(char char_v);
struct node* make_string_literal(char* string_v);
struct node* make_unary_exp(int op, struct node* operand);
struct node* make_binary_exp(struct node* left, int op, struct node* right);
struct node* make_ternary_exp(struct node* condition,
                              struct node* exp1,
                              struct node* exp2);
struct node* make_exp_list(struct node* exp_list, struct node* exp);
struct node* make_switch_cmd(struct node* control_exp, struct node* cmd_block);
struct node* make_do_while_cmd(struct node* cmd_block, struct node* condition);
struct node* make_while_cmd(struct node* condition, struct node* cmd_block);
struct node* make_for_cmd(struct node* initialization,
                          struct node* condition,
                          struct node* update,
                          struct node* cmd_block);
struct node* make_foreach_cmd(char* item,
                              struct node* exp_list,
                              struct node* cmd_block);
struct node* make_dot_arg();
struct node* make_arg_list(struct node* arg_list, struct node* arg);
struct node* make_function_cmd(struct token token, struct node* arg_list);
struct node* make_pipe_cmd(struct node* pipe_cmd,
                           int pipe_op,
                           struct node* function_cmd);
struct node* make_if_cmd(struct node* condition,
                         struct node* then_cmd_block,
                         struct node* else_cmd_block);
struct node* make_out_cmd(struct node* exp_list);
struct node* make_in_cmd(struct node* exp);
struct node* make_case_label(int case_val);
struct node* make_return_cmd(struct node* exp);
struct node* make_shift_cmd(struct node* var, int shift_op, struct node* exp);
struct node* make_break_cmd();
struct node* make_continue_cmd();
struct node* make_var(struct token token,
                      char* field_access,
                      struct node* array_access);
struct node* make_attr_cmd(struct node* var, struct node* exp);
struct node* make_class_var_decl(char* type, struct token token);
struct node* make_var_decl(int type, struct token token, struct node* init);
struct node* add_decl_modifier(bool is_static,
                               bool is_const,
                               struct node* decl);
struct node* make_cmd_list(struct node* cmd_list, struct node* cmd);
struct node* make_high_list(struct node* high_list, struct node* cmd);
struct node* make_cmd_block(struct node* high_list);
struct type make_primitive(int type);
struct type make_custom(char* type);
struct node* make_parameter(bool is_const,
                            struct type type,
                            struct token token);
struct node* make_param_list(struct node* param_list, struct node* param);
struct node* make_function_def(bool is_static,
                               struct type type,
                               struct token token,
                               struct node* params,
                               struct node* cmd_block);
struct node* make_field(enum access_modifier access,
                        struct type type,
                        struct token token);
struct node* make_class_def(struct token token, struct node* field_list);
struct node* make_global_var_decl(struct token token,
                                  int size,
                                  bool is_static,
                                  struct type type);
struct node* make_unit(struct node* unit, struct node* element);

void free_node(struct node* node);
void decompile_node(struct node* node);

#endif

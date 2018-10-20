#include "node.h"

enum status {
    SUCCESS = 0,
    ERROR_UNDECLARED = 10,
    ERROR_ALREADY_DECLARED = 11,
    ERROR_IS_VARIABLE = 20,
    ERROR_IS_VECTOR = 21,
    ERROR_IS_FUNCTION = 22,
    ERROR_IS_USER = 23,
    ERROR_MISMATCHED_TYPE = 30,
    ERROR_IMPLICIT_CONVERSION_STRING = 31,
    ERROR_IMPLICIT_CONVERSION_CHAR = 32,
    ERROR_IMPLICIT_CONVERSION_USER = 33,
    ERROR_MISSING_ARGS = 40,
    ERROR_TOO_MANY_ARGS = 41,
    ERROR_MISMATCHED_TYPE_ARGS = 42,
    ERROR_MISMATCHED_TYPE_INPUT = 50,
    ERROR_MISMATCHED_TYPE_OUTPUT = 51,
    ERROR_MISMATCHED_TYPE_RETURN = 52
};

enum var_access {
    ACCESS_PRIMITIVE,
    ACCESS_CLASS,
    ACCESS_PRIMITIVE_ARRAY,
    ACCESS_CLASS_ARRAY,
    ACCESS_FUNCTION
};

struct analyze_result {
    enum status status;
    struct type type;
};

extern const char* error_msg[];

enum symbol_type {
    SYMBOL_CLASS_DEF,
    SYMBOL_GLOBAL_VAR_DECL,
    SYMBOL_FUNCTION_DEF,
    SYMBOL_PARAM,
    SYMBOL_LOCAL_VAR_DECL
};

struct symbol {
    char* id;
    enum symbol_type type;
    union node_value data;
    enum var_access var_access;

    bool is_new_context;
    struct symbol* next;
};

struct table {
    struct symbol* head;
};

struct table* alloc_table();
void free_table(struct table* table);

struct analyze_result analyze_node(struct node* node, struct table* table);
struct analyze_result define_class(struct class_def class_def,
                                   struct table* table);
struct analyze_result declare_global_var(struct global_var_decl global_var,
                                         struct table* table);
struct analyze_result define_function(struct function_def function_def,
                                      struct table* table);
struct analyze_result declare_local_var(struct local_var_decl local_var,
                                        struct table* table);
struct analyze_result analyze_var(struct var var, struct table* table);
struct analyze_result analyze_return(struct return_cmd return_cmd,
                                     struct table* table);
struct analyze_result analyze_attr(struct attr_cmd attr_cmd,
                                   struct table* table);
struct analyze_result analyze_shift(struct shift_cmd shift_cmd,
                                    struct table* table);
struct analyze_result analyze_for(struct for_cmd for_cmd, struct table* table);
struct analyze_result analyze_function(struct function_cmd function_cmd,
                                       struct table* table);
struct analyze_result analyze_binary(struct binary_exp binary_exp,
                                     struct table* table);
struct analyze_result analyze_ternary(struct ternary_exp ternary_exp,
                                      struct table* table);
struct analyze_result analyze_input(struct in_cmd in_cmd, struct table* table);
struct analyze_result analyze_output(struct out_cmd out_cmd,
                                     struct table* table);

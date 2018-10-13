#include "node.h"

enum analyze_result {
    SUCCESS = 0,
    ERROR_UNDECLARED = 100,
    ERROR_ALREADY_DECLARED = 101,
    ERROR_IS_VARIABLE = 200,
    ERROR_IS_VECTOR = 201,
    ERROR_IS_FUNCTION = 202,
    ERROR_IS_USER = 203,
    ERROR_MISMATCHED_TYPE = 300,
    ERROR_IMPLICIT_CONVERSION_STRING = 301,
    ERROR_IMPLICIT_CONVERSION_CHAR = 302,
    ERROR_IMPLICIT_CONVERSION_USER = 303,
    ERROR_MISSING_ARGS = 400,
    ERROR_TOO_MANY_ARGS = 401,
    ERROR_MISMATCHED_TYPE_ARGS = 402,
    ERROR_MISMATCHED_TYPE_INPUT = 500,
    ERROR_MISMATCHED_TYPE_OUTPUT = 501,
    ERROR_MISMATCHED_TYPE_RETURN = 502
};

extern const char* error_msg[];

enum symbol_type {
    SYMBOL_CLASS_DEF,
    SYMBOL_GLOBAL_VAR_DECL,
    SYMBOL_FUNCTION_DEF,
    SYMBOL_PARAM
};

union symbol_data {
    struct node* fields_head;
    struct type type;
};

struct symbol {
    char* id;
    enum symbol_type type;
    union node_value data;

    bool is_new_context;
    struct symbol* next;
};

struct table {
    struct symbol* head;
};

struct table* alloc_table();
void free_table(struct table* table);
bool is_declared(char* id, struct table* table);

enum analyze_result analyze_node(struct node* node, struct table* table);
enum analyze_result define_class(struct class_def class_def,
                                 struct table* table);
enum analyze_result declare_global_var(struct global_var_decl global_var,
                                       struct table* table);
enum analyze_result define_function(struct function_def function_def,
                                    struct table* table);

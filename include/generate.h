#include "node.h"

enum instruction_constant {
    STORE_AI,
    LOAD_I,
    LOAD_AI,
    ADD,
    SUB,
    MULT,
    DIV,
    CMP_LT,
    CMP_LE,
    CMP_GT,
    CMP_GE,
    CMP_EQ,
    CMP_NE,
    CBR,
    JUMP_I,
    LABEL,
    FLABEL,
    I2I,
    ADD_I,
    JUMP
};

enum scope { GLOBAL, LOCAL };

struct address {
    char* id;
    int offset;
    enum scope scope;
    struct address* next;
};

struct offset_table {
    struct address* head;
};

struct offset_table* alloc_offset_table();
void free_offset_table(struct offset_table* table);

void generate_code(struct node* node);
void generate(struct node* node,
              struct offset_table* table,
              char* l_true,
              char* l_false);
void generate_global_var(struct global_var_decl global_var,
                         struct offset_table* table);
void generate_local_var(struct local_var_decl local_var,
                        struct offset_table* table);
void generate_attribution(struct attr_cmd attr, struct offset_table* table);
void generate_literal(struct token literal);
void generate_var(struct var var, struct offset_table* table);
void generate_binary(struct binary_exp binary_exp,
                     struct offset_table* table,
                     char* l_true,
                     char* l_false);
void generate_if(struct if_cmd if_cmd, struct offset_table* table);
void generate_while(struct while_cmd while_cmd, struct offset_table* table);
void generate_do_while(struct do_while_cmd do_while_cmd,
                       struct offset_table* table);
void generate_function_def(struct function_def function_def,
                           struct offset_table* table);
void generate_return(struct return_cmd return_cmd, struct offset_table* table);
void generate_function(struct function_cmd function_cmd,
                       struct offset_table* table);

struct ins {
    char* line;
    struct ins* next;
};

struct code {
    struct ins* head;
    struct ins* last;
};

char* alloc_line();
void append_ins(char* line);
void free_code(struct ins* head);
void print_code();

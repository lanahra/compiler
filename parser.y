%{
#include <stdio.h>
#include "../include/lex.yy.h"

int yylex();
void yyerror(char const *s);
extern int get_line_number();
extern int get_column_number();
%}

%code requires {
#include <stdbool.h>

union value {
    int int_v;
    float float_v;
    char char_v;
    char* string_v;
    bool bool_v;
};
}

%union {
    struct token {
        int line;
        int column;
        enum yytokentype type;
        union value val;
    } token;
}

%token INT
%token FLOAT
%token BOOL
%token CHAR
%token STRING
%token IF
%token THEN
%token ELSE
%token WHILE
%token DO
%token INPUT
%token OUTPUT
%token RETURN
%token CONST
%token STATIC
%token FOREACH
%token FOR
%token SWITCH
%token CASE
%token BREAK
%token CONTINUE
%token CLASS
%token PRIVATE
%token PUBLIC
%token PROTECTED
%token LE_OP
%token GE_OP
%token EQ_OP
%token NE_OP
%token AND_OP
%token OR_OP
%token SL_OP
%token SR_OP
%token FORWARD_PIPE
%token BASH_PIPE
%token INT_LITERAL
%token FLOAT_LITERAL
%token FALSE
%token TRUE
%token CHAR_LITERAL
%token <token.val.string_v> STRING_LITERAL
%token <token.val.string_v> ID
%token ERROR

%start program
%%

program
    : %empty
    | unit
    ;

unit
    : element
    | unit element
    ;

element
    : element_definition
    | class_definition ';'
    ;

element_definition
    : ID global_var_declaration ';' { free($1); }
    | ID ID element_specifier { free($1); free($2); }
    | function_definition
    ;

global_var_declaration
    : global_var_type_specifier
    | array global_var_type_specifier
    | array global_var_class_specifier
    ;

global_var_type_specifier
    : static_modifier primitive_type_specifier
    ;

global_var_class_specifier
    : static_modifier ID { free($2); }
    ;

array
    : '[' INT_LITERAL ']'
    ;

static_modifier
    : %empty
    | STATIC
    ;

const_modifier
    : %empty
    | CONST
    ;

primitive_type_specifier
    : INT
    | FLOAT
    | BOOL
    | CHAR
    | STRING
    ;

literal
    : INT_LITERAL
    | FLOAT_LITERAL
    | FALSE
    | TRUE
    | CHAR_LITERAL
    | STRING_LITERAL { free($1); }
    ;

type_specifier
    : primitive_type_specifier
    | ID { free($1); }
    ;

element_specifier
    : ';'
    | parameters command_block
    ;

class_definition
    : CLASS ID '[' field_list ']' { free($2); }
    ;

field_list
    : field
    | field_list ':' field
    ;

field
    : access_modifier primitive_type_specifier ID { free($3); }
    ;

access_modifier
    : %empty
    | PRIVATE
    | PUBLIC
    | PROTECTED
    ;

function_definition
    : function_header command_block
    ;

function_header
    : static_modifier primitive_type_specifier ID parameters { free($3); }
    ;

parameters
    : '(' ')'
    | '(' parameter_list ')'
    ;

parameter_list
    : parameter
    | parameter_list ',' parameter
    ;

parameter
    : const_modifier type_specifier ID { free($3); }
    ;

command_block
    : '{' '}'
    | '{' high_command_list '}'
    ;

high_command_list
    : high_command
    | high_command_list high_command
    ;

high_command
    : command ';'
    | output ';'
    | case
    ;

command_list
    : command
    | command_list ',' command

command
    : local_var_declaration
    | variable_attribution
    | shift
    | return
    | BREAK
    | CONTINUE
    | input
    | conditional_statement
    | function_call
    | foreach
    | for
    | while
    | do_while
    | switch
    | command_block
    ;

local_var_declaration
    : static_modifier const_modifier local_var_specifier
    ;

local_var_specifier
    : primitive_type_specifier ID local_var_initialization { free($2); }
    ;

local_var_initialization
    : %empty
    | LE_OP local_var_initializer
    ;

local_var_initializer
    : ID { free($1); }
    | literal
    ;

variable_attribution
    : ID ID { free($1); free($2); }
    | variable '=' expression
    ;

variable
    : ID { free($1); }
    | ID '$' ID { free($1); free($3); }
    | ID '[' expression ']' { free($1); }
    | ID '[' expression ']' '$' ID { free($1); free($6); }
    ;

shift
    : variable SL_OP expression
    | variable SR_OP expression
    ;

return
    : RETURN expression
    ;

case
    : CASE INT_LITERAL ':'
    ;

input
    : INPUT expression

output
    : OUTPUT expression_list
    ;

conditional_statement
    : IF '(' expression ')' THEN command_block else_statement
    ;

else_statement
    : %empty
    | ELSE command_block
    ;

function_call
    : function
    | function_call pipe function
    ;

function
    : ID '(' argument_list ')' { free($1); }
    ;

pipe
    : FORWARD_PIPE
    | BASH_PIPE
    ;

argument_list
    : %empty
    | argument
    | argument_list ',' argument
    ;

argument
    : '.'
    | expression
    ;

foreach
    : FOREACH '(' ID ':' expression_list ')' command_block { free($3); }
    ;

for
    : FOR '(' command_list ':' expression ':' command_list ')' command_block
    ;

while
    : WHILE '(' expression ')' DO command_block
    ;

do_while
    : DO command_block WHILE '(' expression ')'

switch
    : SWITCH '(' expression ')' command_block
    ;

expression_list
    : expression
    | expression_list ',' expression
    ;

expression
    : pipe_exp
    ;

pipe_exp
    : ternary_exp
    | pipe_exp FORWARD_PIPE ternary_exp
    | pipe_exp BASH_PIPE ternary_exp
    ;

ternary_exp
    : logical_or_exp
    | logical_or_exp '?' expression ':' ternary_exp

logical_or_exp
    : logical_and_exp
    | logical_or_exp OR_OP logical_and_exp
    ;

logical_and_exp
    : bitwise_or_exp
    | logical_and_exp AND_OP bitwise_or_exp
    ;

bitwise_or_exp
    : bitwise_and_exp
    | bitwise_or_exp '|' bitwise_and_exp
    ;

bitwise_and_exp
    : equality_exp
    | bitwise_and_exp '&' equality_exp
    ;

equality_exp
    : relational_exp
    | equality_exp EQ_OP relational_exp
    | equality_exp NE_OP relational_exp
    ;

relational_exp
    : additive_exp
    | relational_exp '<' additive_exp
    | relational_exp '>' additive_exp
    | relational_exp LE_OP additive_exp
    | relational_exp GE_OP additive_exp
    ;

additive_exp
    : multiplicative_exp
    | additive_exp '+' multiplicative_exp
    | additive_exp '-' multiplicative_exp
    ;

multiplicative_exp
    : exponentiation_exp
    | multiplicative_exp '*' exponentiation_exp
    | multiplicative_exp '/' exponentiation_exp
    | multiplicative_exp '%' exponentiation_exp
    ;

exponentiation_exp
    : unary_exp
    | exponentiation_exp '^' unary_exp
    ;

unary_exp
    : operand
    | unary_operator unary_exp
    ;

unary_operator
    : '+'
    | '-'
    | '!'
    | '*'
    | '&'
    | '?'
    | '#'
    ;

operand
    : variable
    | literal
    | function
    | '(' expression ')'
    ;

%%

void yyerror(char const *s) {
    char error[] = "Unexpected token: %s at line %d column %d\n";
    fprintf(stderr, error, yytext, get_line_number(), get_column_number());
}

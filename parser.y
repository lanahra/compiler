%{
#include <stdio.h>
#include "lex.yy.h"
int yylex();
void yyerror(char const *s);
extern int get_line_number();
extern int get_column_number();
%}

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
%token STRING_LITERAL
%token ID
%token ERROR

%start unit
%%

unit
    : element
    | unit element
    ;

element
    : element_definition
    | class_definition ';'
    ;

element_definition
    : ID global_var_declaration ';'
    | ID ID element_specifier
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
    : static_modifier ID
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
    | STRING_LITERAL
    ;

type_specifier
    : primitive_type_specifier
    | ID
    ;

element_specifier
    : ';'
    | parameters command_block
    ;

class_definition
    : CLASS ID '[' field_list ']'
    ;

field_list
    : field
    | field_list ':' field
    ;

field
    : access_modifier primitive_type_specifier ID
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
    : static_modifier primitive_type_specifier ID parameters
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
    : const_modifier type_specifier ID
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
    : command
    | case
    | input ';'
    | output ';'
    ;

command
    : local_var_declaration ';'
    | variable_attribution ';'
    | shift_op ';'
    | return ';'
    | BREAK ';'
    | CONTINUE ';'
    | conditional_statement
    | function_call ';'
    | foreach
    ;

local_var_declaration
    : static_modifier const_modifier local_var_specifier
    ;

local_var_specifier
    : primitive_type_specifier ID local_var_initialization
    ;

local_var_initialization
    : %empty
    | LE_OP local_var_initializer
    ;

local_var_initializer
    : ID
    | literal
    ;

variable_attribution
    : ID ID
    | ID '=' expression
    | ID '[' expression ']' '=' expression
    | ID '$' ID '=' expression
    ;

shift_op
    : ID SL_OP INT_LITERAL
    | ID SR_OP INT_LITERAL
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
    : ID '(' argument_list ')'
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
    : FOREACH '(' ID ':' expression_list ')' command_block
    ;

expression_list
    : expression
    | expression_list ',' expression
    ;

expression
    : ID
    ;

%%

void yyerror(char const *s) {
    char error[] = "Unexpected token: %s at line %d column %d\n";
    fprintf(stderr, error, yytext, get_line_number(), get_column_number());
}

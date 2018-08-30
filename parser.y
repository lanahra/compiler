%{
#include <stdio.h>
int yylex();
void yyerror(char const *s);
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
    : global_var_declaration ';'
    | class_definition ';'
    ;

global_var_declaration
    : declarator type_specifier
    | declarator STATIC type_specifier
    ;

declarator
    : ID
    | ID array
    ;

array
    : '[' INT_LITERAL ']'
    ;

type_specifier
    : type
    | ID
    ;

type
    : INT
    | FLOAT
    | BOOL
    | CHAR
    | STRING
    ;

class_definition
    : CLASS ID '[' field_list ']'
    ;

field_list
    : field
    | field_list ':' field
    ;

field
    : type ID
    | access_modifier type ID
    ;

access_modifier
    : PRIVATE
    | PUBLIC
    | PROTECTED
    ;

%%

void yyerror(char const *s) {
   fprintf(stderr, "%s\n", s);
}

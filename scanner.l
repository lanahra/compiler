%{
#include "tokens.h"

char unexpected_token_error[] = "Unexpected token: %s at line %d\n";
%}

LINE_COMMENT "//".*
ID [a-zA-Z][a-zA-Z0-9]*
INTEGER [-+]?[0-9]+
FLOAT {INTEGER}"."[0-9]+([eE]{INTEGER})?
CHAR '(.|\n)?'
STRING \"(\\.|[^\\"])*\"

%option yylineno

%x BLOCK_COMMENT

%%

{LINE_COMMENT} {
   // ignore line comment
}

"/*" {
    BEGIN(BLOCK_COMMENT);
}

<BLOCK_COMMENT>{
"*/" {
    BEGIN(INITIAL);
}

[^*]+ {
    // ignore block comment in chunks
}

"*" {
    // ignore asterisk inside block comment
}
}

[ \t]+ {
    // ignore whitespace
}

\n {
    // ignore new line
}

"int" {
    return TK_PR_INT;
}

"float" {
    return TK_PR_FLOAT;
}

"bool" {
    return TK_PR_BOOL;
}

"char" {
    return TK_PR_CHAR;
}

"string" {
    return TK_PR_STRING;
}

"if" {
    return TK_PR_IF;
}

"then" {
    return TK_PR_THEN;
}

"else" {
    return TK_PR_ELSE;
}

"while" {
    return TK_PR_WHILE;
}

"do" {
    return TK_PR_DO;
}

"input" {
    return TK_PR_INPUT;
}

"output" {
    return TK_PR_OUTPUT;
}

"return" {
    return TK_PR_RETURN;
}

"const" {
    return TK_PR_CONST;
}

"static" {
    return TK_PR_STATIC;
}

"foreach" {
    return TK_PR_FOREACH;
}

"for" {
    return TK_PR_FOR;
}

"switch" {
    return TK_PR_SWITCH;
}

"case" {
    return TK_PR_CASE;
}

"break" {
    return TK_PR_BREAK;
}

"continue" {
    return TK_PR_CONTINUE;
}

"class" {
    return TK_PR_CLASS;
}

"private" {
    return TK_PR_PRIVATE;
}

"public" {
    return TK_PR_PUBLIC;
}

"protected" {
    return TK_PR_PROTECTED;
}

"<=" {
    return TK_OC_LE;
}

">=" {
    return TK_OC_GE;
}

"==" {
    return TK_OC_EQ;
}

"!=" {
    return TK_OC_NE;
}

"&&" {
    return TK_OC_AND;
}

"||" {
    return TK_OC_OR;
}

"<<" {
    return TK_OC_SL;
}

">>" {
    return TK_OC_SR;
}

"%>%" {
    return TK_OC_FORWARD_PIPE;
}

"%|%" {
    return TK_OC_BASH_PIPE;
}

"," |
";" |
":" |
"(" |
")" |
"[" |
"]" |
"{" |
"}" |
"+" |
"-" |
"|" |
"?" |
"*" |
"/" |
"<" |
">" |
"=" |
"!" |
"&" |
"%" |
"#" |
"^" |
"." |
"$" {
    return (int) yytext[0];
}

"false" {
    return TK_LIT_FALSE;
}

"true" {
    return TK_LIT_TRUE;
}

{INTEGER} {
    return TK_LIT_INT;
}

{FLOAT} {
    return TK_LIT_FLOAT;
}

{CHAR} {
    return TK_LIT_CHAR;
}

{STRING} {
    return TK_LIT_STRING;
}

{ID} {
    return TK_IDENTIFICADOR;
}

. {
    printf(unexpected_token_error, yytext, yylineno);
    return 0;
}

%%

int get_line_number() {
    return yylineno;
}

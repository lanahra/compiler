%{
#include "parser.tab.h"

int column = 1;

void count();
%}

LINE_COMMENT "//".*
ID [a-zA-Z_][a-zA-Z_0-9]*
INTEGER [-+]?[0-9]+
FLOAT {INTEGER}"."[0-9]+([eE]{INTEGER})?
CHAR '.'
STRING \"(\\.|[^\\"])*\"

%option yylineno

%x BLOCK_COMMENT

%%

{LINE_COMMENT} {
    // ignore line comment
    count();
}

"/*" {
    count();
    BEGIN(BLOCK_COMMENT);
}

<BLOCK_COMMENT>{
"*/" {
    count();
    BEGIN(INITIAL);
}

[^*]+ {
    // ignore block comment in chunks
    count();
}

"*" {
    // ignore asterisk inside block comment
    count();
}
}

[ \t\n]+ {
    // ignore whitespace
    count();
}

"int" {
    count();
    return TK_PR_INT;
}

"float" {
    count();
    return TK_PR_FLOAT;
}

"bool" {
    count();
    return TK_PR_BOOL;
}

"char" {
    count();
    return TK_PR_CHAR;
}

"string" {
    count();
    return TK_PR_STRING;
}

"if" {
    count();
    return TK_PR_IF;
}

"then" {
    count();
    return TK_PR_THEN;
}

"else" {
    count();
    return TK_PR_ELSE;
}

"while" {
    count();
    return TK_PR_WHILE;
}

"do" {
    count();
    return TK_PR_DO;
}

"input" {
    count();
    return TK_PR_INPUT;
}

"output" {
    count();
    return TK_PR_OUTPUT;
}

"return" {
    count();
    return TK_PR_RETURN;
}

"const" {
    count();
    return TK_PR_CONST;
}

"static" {
    count();
    return TK_PR_STATIC;
}

"foreach" {
    count();
    return TK_PR_FOREACH;
}

"for" {
    count();
    return TK_PR_FOR;
}

"switch" {
    count();
    return TK_PR_SWITCH;
}

"case" {
    count();
    return TK_PR_CASE;
}

"break" {
    count();
    return TK_PR_BREAK;
}

"continue" {
    count();
    return TK_PR_CONTINUE;
}

"class" {
    count();
    return TK_PR_CLASS;
}

"private" {
    count();
    return TK_PR_PRIVATE;
}

"public" {
    count();
    return TK_PR_PUBLIC;
}

"protected" {
    count();
    return TK_PR_PROTECTED;
}

"<=" {
    count();
    return TK_OC_LE;
}

">=" {
    count();
    return TK_OC_GE;
}

"==" {
    count();
    return TK_OC_EQ;
}

"!=" {
    count();
    return TK_OC_NE;
}

"&&" {
    count();
    return TK_OC_AND;
}

"||" {
    count();
    return TK_OC_OR;
}

"<<" {
    count();
    return TK_OC_SL;
}

">>" {
    count();
    return TK_OC_SR;
}

"%>%" {
    count();
    return TK_OC_FORWARD_PIPE;
}

"%|%" {
    count();
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
    count();
    return (int) yytext[0];
}

"false" {
    count();
    return TK_LIT_FALSE;
}

"true" {
    count();
    return TK_LIT_TRUE;
}

{INTEGER} {
    count();
    return TK_LIT_INT;
}

{FLOAT} {
    count();
    return TK_LIT_FLOAT;
}

{CHAR} {
    count();
    return TK_LIT_CHAR;
}

{STRING} {
    count();
    return TK_LIT_STRING;
}

{ID} {
    count();
    return TK_IDENTIFICADOR;
}

. {
    count();
    return TOKEN_ERRO;
}

%%

void count() {
    int i;

    for (i = 0; yytext[i] != '\0'; i++) {
        if (yytext[i] == '\n') {
            column = 1;
        } else {
            column++;
        }
    }
}

int get_line_number() {
    return yylineno;
}

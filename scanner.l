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
    return INT;
}

"float" {
    count();
    return FLOAT;
}

"bool" {
    count();
    return BOOL;
}

"char" {
    count();
    return CHAR;
}

"string" {
    count();
    return STRING;
}

"if" {
    count();
    return IF;
}

"then" {
    count();
    return THEN;
}

"else" {
    count();
    return ELSE;
}

"while" {
    count();
    return WHILE;
}

"do" {
    count();
    return DO;
}

"input" {
    count();
    return INPUT;
}

"output" {
    count();
    return OUTPUT;
}

"return" {
    count();
    return RETURN;
}

"const" {
    count();
    return CONST;
}

"static" {
    count();
    return STATIC;
}

"foreach" {
    count();
    return FOREACH;
}

"for" {
    count();
    return FOR;
}

"switch" {
    count();
    return SWITCH;
}

"case" {
    count();
    return CASE;
}

"break" {
    count();
    return BREAK;
}

"continue" {
    count();
    return CONTINUE;
}

"class" {
    count();
    return CLASS;
}

"private" {
    count();
    return PRIVATE;
}

"public" {
    count();
    return PUBLIC;
}

"protected" {
    count();
    return PROTECTED;
}

"<=" {
    count();
    return LE_OP;
}

">=" {
    count();
    return GE_OP;
}

"==" {
    count();
    return EQ_OP;
}

"!=" {
    count();
    return NE_OP;
}

"&&" {
    count();
    return AND_OP;
}

"||" {
    count();
    return OR_OP;
}

"<<" {
    count();
    return SL_OP;
}

">>" {
    count();
    return SR_OP;
}

"%>%" {
    count();
    return FORWARD_PIPE;
}

"%|%" {
    count();
    return BASH_PIPE;
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
    return FALSE;
}

"true" {
    count();
    return TRUE;
}

{INTEGER} {
    count();
    return INT_LITERAL;
}

{FLOAT} {
    count();
    return FLOAT_LITERAL;
}

{CHAR} {
    count();
    return CHAR_LITERAL;
}

{STRING} {
    count();
    return STRING_LITERAL;
}

{ID} {
    count();
    return ID;
}

. {
    count();
    return ERROR;
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

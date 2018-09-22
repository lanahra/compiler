%{
#include <stdlib.h>
#include <string.h>
#include "../include/parser.tab.h"

int columnno = 1;

void assign_token_value(int type);
void count_column();
%}

LINE_COMMENT "//".*
ID [a-zA-Z_][a-zA-Z_0-9]*
INTEGER [0-9]+
FLOAT {INTEGER}"."[0-9]+([eE][-+]?{INTEGER})?
CHAR '.'
STRING \"(\\.|[^\\"])*\"

%option yylineno
%option noinput
%option nounput

%x BLOCK_COMMENT

%%

{LINE_COMMENT} {
    // ignore line comment
    count_column();
}

"/*" {
    count_column();
    BEGIN(BLOCK_COMMENT);
}

<BLOCK_COMMENT>{
"*/" {
    count_column();
    BEGIN(INITIAL);
}

[^*]+ {
    // ignore block comment in chunks
    count_column();
}

"*" {
    // ignore asterisk inside block comment
    count_column();
}
}

[ \t\n]+ {
    // ignore whitespace
    count_column();
}

"int" {
    assign_token_value(INT);
    count_column();
    return INT;
}

"float" {
    assign_token_value(FLOAT);
    count_column();
    return FLOAT;
}

"bool" {
    assign_token_value(BOOL);
    count_column();
    return BOOL;
}

"char" {
    assign_token_value(CHAR);
    count_column();
    return CHAR;
}

"string" {
    assign_token_value(STRING);
    count_column();
    return STRING;
}

"if" {
    count_column();
    return IF;
}

"then" {
    count_column();
    return THEN;
}

"else" {
    count_column();
    return ELSE;
}

"while" {
    count_column();
    return WHILE;
}

"do" {
    count_column();
    return DO;
}

"input" {
    count_column();
    return INPUT;
}

"output" {
    count_column();
    return OUTPUT;
}

"return" {
    count_column();
    return RETURN;
}

"const" {
    count_column();
    return CONST;
}

"static" {
    count_column();
    return STATIC;
}

"foreach" {
    count_column();
    return FOREACH;
}

"for" {
    count_column();
    return FOR;
}

"switch" {
    count_column();
    return SWITCH;
}

"case" {
    count_column();
    return CASE;
}

"break" {
    count_column();
    return BREAK;
}

"continue" {
    count_column();
    return CONTINUE;
}

"class" {
    count_column();
    return CLASS;
}

"private" {
    count_column();
    return PRIVATE;
}

"public" {
    count_column();
    return PUBLIC;
}

"protected" {
    count_column();
    return PROTECTED;
}

"<=" {
    assign_token_value(LE_OP);
    count_column();
    return LE_OP;
}

">=" {
    assign_token_value(GE_OP);
    count_column();
    return GE_OP;
}

"==" {
    assign_token_value(EQ_OP);
    count_column();
    return EQ_OP;
}

"!=" {
    assign_token_value(NE_OP);
    count_column();
    return NE_OP;
}

"&&" {
    assign_token_value(AND_OP);
    count_column();
    return AND_OP;
}

"||" {
    assign_token_value(OR_OP);
    count_column();
    return OR_OP;
}

"<<" {
    assign_token_value(SL_OP);
    count_column();
    return SL_OP;
}

">>" {
    assign_token_value(SR_OP);
    count_column();
    return SR_OP;
}

"%>%" {
    assign_token_value(FORWARD_PIPE);
    count_column();
    return FORWARD_PIPE;
}

"%|%" {
    assign_token_value(BASH_PIPE);
    count_column();
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
    int token = (int) yytext[0];
    assign_token_value(token);
    count_column();
    return token;
}

"false" {
    assign_token_value(FALSE);
    count_column();
    return FALSE;
}

"true" {
    assign_token_value(TRUE);
    count_column();
    return TRUE;
}

{INTEGER} {
    assign_token_value(INT_LITERAL);
    count_column();
    return INT_LITERAL;
}

{FLOAT} {
    assign_token_value(FLOAT_LITERAL);
    count_column();
    return FLOAT_LITERAL;
}

{CHAR} {
    assign_token_value(CHAR_LITERAL);
    count_column();
    return CHAR_LITERAL;
}

{STRING} {
    assign_token_value(STRING_LITERAL);
    count_column();
    return STRING_LITERAL;
}

{ID} {
    assign_token_value(ID);
    count_column();
    return ID;
}

. {
    return ERROR;
}

%%

void assign_token_value(int type) {
    yylval.token.line = yylineno;
    yylval.token.column = columnno;
    yylval.token.type = type;

    union literal val;

    switch (type) {
        case INT_LITERAL:
            val.int_v = atoi(yytext);
            break;
        case FLOAT_LITERAL:
            val.float_v = atof(yytext);
            break;
        case CHAR_LITERAL:
            val.char_v = yytext[1];
            break;
        case STRING_LITERAL:
            val.string_v = strndup(yytext + 1, strlen(yytext) - 2);
            break;
        case ID:
            val.string_v = strdup(yytext);
            break;
        case FALSE:
            val.bool_v = false;
            break;
        case TRUE:
            val.bool_v = true;
            break;
        default:
            break;
    }

    yylval.token.val = val;
}

void count_column() {
    int i;

    for (i = 0; yytext[i] != '\0'; i++) {
        if (yytext[i] == '\n') {
            columnno = 1;
        } else {
            columnno++;
        }
    }
}

int get_line_number() {
    return yylineno;
}

int get_column_number() {
    return columnno;
}

%{
#include "tokens.h"
%}

LINE_COMMENT "//".*

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

. {
    return yytext[0];
}

%%

int get_line_number() {
    return yylineno;
}

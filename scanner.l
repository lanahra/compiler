%{
#include "tokens.h"

int line_number = 1;
%}

%%

\n {
    line_number++;
}

. {
    return yytext[0];
}

%%

int get_line_number() {
    return line_number;
}

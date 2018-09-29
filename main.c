#include <stdio.h>
#include "include/lex.yy.h"
#include "include/parser.tab.h"

void *arvore = 0;
void descompila(void *arvore);
void libera(void *arvore);

int main() {
    int status = yyparse();
    descompila(arvore);
    libera(arvore);
    arvore = 0;
    yylex_destroy();
    return status;
}

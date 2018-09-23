/*
Função principal para realização da E3.

Este arquivo não pode ser modificado.
*/
#include <stdio.h>
#include "include/lex.yy.h"
#include "include/parser.tab.h"  //arquivo gerado com bison -d parser.y

void *arvore = 0;
void descompila(void *arvore);
void libera(void *arvore);

int main() {
    int ret = yyparse();
    descompila(arvore);
    libera(arvore);
    arvore = 0;
    yylex_destroy();
    return ret;
}

#include <stdio.h>
#include "include/parser.tab.h"

int main (int argc, char **argv) {
    return yyparse();
}

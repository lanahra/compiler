#include <stdio.h>
#include "include/analyze.h"
#include "include/lex.yy.h"
#include "include/parser.tab.h"

int main(int argc, char** argv) {
    (void)argc;
    (void)argv;

    struct node* node = 0;
    int status = yyparse(&node);

    if (status != 0) {
        free_node(node);
        yylex_destroy();
        exit(status);
    }

    struct table* table = alloc_table();
    struct analyze_result result = analyze_node(node, table);

    free_table(table);
    free_node(node);
    yylex_destroy();

    return result.status;
}


#include "lexer.h"
#include "ast.h"
#include "parser.h"
#include <stdio.h>

int main() {
    fprintf(stderr, "ready> ");
    get_next_tok();

    ASTNode *expr = parse_entry(); // Change to parse arithmetic expressions
    if (expr) {
        fprintf(stderr, "Parsed arithmetic expression.\n");
        // TODO: print AST or evaluate
    } else {
        fprintf(stderr, "Parse error.\n");
    }
    return 0;
}
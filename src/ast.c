#include "ast.h"
#include "lexer.h"
#include <stdio.h>

variableExprAST lhs =  {EXPR_VARIABLE, "x" };
variableExprAST rhs =  {EXPR_VARIABLE, "y"};
binaryExprAST result = {EXPR_BINARY, '+', &lhs, &rhs};

int get_next_tok() {
    return cur_tok = get_tok();
}

exprAST* log_error(char *str) {
    fprintf(stderr, "Error: %s\n", str);
    return NULL;
}

prototypeAST* log_error_p(char *str) {
    log_error(str);
    return NULL;
}
#include <stdio.h>
#include "lexer.h"
#include "ast.h"
#include "parser.h"

int main() {
    BinopPrecedence['<'] = 10;
    BinopPrecedence['+'] = 20;
    BinopPrecedence['-'] = 20;
    BinopPrecedence['*'] = 40;
    return 0;
}
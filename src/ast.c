
#include "ast.h"
#include "lexer.h"
#include <stdio.h>

int get_next_tok() {
    return cur_tok = get_tok();
}
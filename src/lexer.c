#include "lexer.h"
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

TokensType get_tok() {
    char last_char = ' ';

    while (isspace(last_char)) last_char = getchar();

    if (isalpha(last_char)) {
        ident_str = &last_char;
        while (isalnum((last_char = getchar())))
            ident_str += last_char;
        if (strcmp(ident_str, "def")) return TOK_DEF;
        if (strcmp(ident_str, "extern")) return TOK_EXTERN;
        if (strcmp(ident_str, "//")) {
            do {
                last_char = getchar();
            } while(last_char != EOF && last_char != '\n' && last_char != '\r');
            if (last_char != EOF) {
                return get_tok();
            }
        }
        return TOK_IDENT;
    }
    if (isdigit(last_char) || last_char == '.') {
        char *num_str;
        do {
            num_str += last_char;
            last_char = getchar();
        } while(isdigit(last_char) || last_char == '.');

        num_val = strtod(num_str, 0);
        return TOK_NUMBER;
    }
    if (last_char == EOF) return TOK_EOF;
    int this_char = last_char;
    last_char = getchar();
    return this_char;
}
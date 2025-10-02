
#include "lexer.h"
#include "parser.h"
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Definitions for global variables
char ident_str[256] = {0};
double num_val = 0.0;
int cur_tok = 0;

TokensType get_tok() {
    char last_char = ' ';
// ...existing code...


    while (isspace(last_char)) last_char = getchar();

    if (isalpha(last_char)) {
        int ident_len = 0;
        // Build identifier string
        do {
            if (ident_len < 255) {
                ident_str[ident_len++] = last_char;
            }
            last_char = getchar();
        } while (isalnum(last_char) || last_char == '_');
        ident_str[ident_len] = '\0';

        // Keyword check
        if (strcmp(ident_str, "def") == 0) return TOK_DEF;
        if (strcmp(ident_str, "extern") == 0) return TOK_EXTERN;
        // ...other keywords if needed...

        return TOK_IDENT;
    }
    if (isdigit(last_char) || last_char == '.') {
        char num_str[256];
        int num_len = 0;
        do {
            if (num_len < 255) {
                num_str[num_len++] = last_char;
            }
            last_char = getchar();
        } while(isdigit(last_char) || last_char == '.');
        num_str[num_len] = '\0';
        num_val = strtod(num_str, 0);
        return TOK_NUMBER;
    }
    if (last_char == EOF) return TOK_EOF;
    int this_char = last_char;
    last_char = getchar();
    return this_char;
}
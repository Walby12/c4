#include "parser.h"
#include "lexer.h"
#include "ast.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static char *strdup_c4(const char *src) {
    if (!src) return NULL;
    size_t len = strlen(src);
    char *dst = malloc(len + 1);
    if (dst) strcpy(dst, src);
    return dst;
}

int get_precedence(int tok) {
    switch (tok) {
        case '+': case '-': return 10;
        case '*': case '/': return 20;
        default: return -1;
    }
}

ASTNode *parse_primary() {
    if (cur_tok == TOK_NUMBER) {
        ASTNode *node = malloc(sizeof(ASTNode));
        node->type = AST_NUMBER;
        node->data.number.value = num_val;
        get_tok();
        return node;
    } else if (cur_tok == TOK_IDENT) {
        ASTNode *node = malloc(sizeof(ASTNode));
        node->type = AST_VARIABLE;
        node->data.variable.name = strdup_c4(ident_str);
        get_tok();
        return node;
    } else if (cur_tok == '(') {
        get_tok();
        ASTNode *expr = parse_expression();
        if (cur_tok != ')') {
            fprintf(stderr, "Expected ')'\n");
            return NULL;
        }
        get_tok();
        return expr;
    } else {
        fprintf(stderr, "Unknown token in primary\n");
        return NULL;
    }
}

ASTNode *parse_binary_rhs(int min_prec, ASTNode *lhs) {
    while (1) {
        int prec = get_precedence(cur_tok);
        if (prec < min_prec) return lhs;
        int op = cur_tok;
        get_tok();
        ASTNode *rhs = parse_primary();
        if (!rhs) return NULL;
        int next_prec = get_precedence(cur_tok);
        if (prec < next_prec) {
            rhs = parse_binary_rhs(prec + 1, rhs);
            if (!rhs) return NULL;
        }
        ASTNode *bin = malloc(sizeof(ASTNode));
        bin->type = AST_BINARY;
        bin->data.binary.op = op;
        bin->data.binary.lhs = lhs;
        bin->data.binary.rhs = rhs;
        lhs = bin;
    }
}

ASTNode *parse_expression() {
    ASTNode *lhs = parse_primary();
    if (!lhs) return NULL;
    return parse_binary_rhs(0, lhs);
}

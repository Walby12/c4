#include "parser.h"
#include "ast.h"
#include "lexer.h"
#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>

exprAST* parse_number_expr() {
    numberExprAST *result = malloc(sizeof(numberExprAST));
    if (!result) {
        eprintf(stderr, "Ran out of memory for numberExprAST\n");
        exit(1);
    }
    result->base.kind = EXPR_NUMBER;
    result->val = num_val;
    get_next_tok();
    return (exprAST*) result;
}

exprAST* parse_paren_expr() {
    get_next_tok();
    exprAST* v = parse_expression();
    if (!v) {
        eprintf(stderr, "Ran out of memory for exprAST\n");
        exit(1);
    }
    if (cur_tok != ')') return log_error("expected ')'");
    get_next_tok();
    return v;
}

exprAST* parse_ident_expr() {
    char *id_name = ident_str;

    get_next_tok();

    if (cur_tok != '(') {
        variableExprAST* v = malloc(sizeof(variableExprAST));
        if (!v) {
            eprintf(stderr, "Ran out of memory for variableExprAST");
            exit(1);
        } 
        v->base.kind = EXPR_VARIABLE;
        v->name = id_name;
        return v;
    }

    get_next_tok();
    exprAST args[MAX];
    int index = 0;

    if (cur_tok != ')') {
        while (true) {
            exprAST* arg = parse_expression();
            if (arg) {
                if (index < MAX) {
                    args[index++] = *arg;
                } else {
                    return NULL;
                }
            }
            if (cur_tok == ')') break;
            
            if (cur_tok != ',') {
                return log_error("Expected ')' or '.' in argument list");
            }
            get_next_tok();
        }
    }
    get_next_tok();

    callExprAST* n = {EXPR_CALL, id_name, *args, index};
    return n;
}

exprAST* parse_primary() {
  switch (cur_tok) {
  default:
    return LogError("unknown token when expecting an expression");
  case TOK_IDENT:
    return ParseIdentifierExpr();
  case TOK_NUMBER:
    return ParseNumberExpr();
  case '(':
    return ParseParenExpr();
  }
}

int get_tok_precedence() {
    if (!isascii(cur_tok)) return -1;
    
    int tok_prec = BinopPrecedence[cur_tok];
    if (tok_prec <= 0) return -1;
    return tok_prec;
}

exprAST* parse_expression() {
    exprAST* lhs = parse_primary();
    if (!lhs) {
        return NULL;
    }
    return parse_bin_op_rhs(0, &lhs);
}

exprAST* parse_bin_op_rhs(int expr_prec, exprAST* lhs) {
    while (true) {
        int tok_prec = get_tok_precedence();

        if (tok_prec < expr_prec) return lhs;

        int bin_op = cur_tok;
        get_next_tok();

        exprAST* rhs = parse_primary();
        if (!rhs) return NULL;

        int next_prec = get_tok_precedence();
        if (tok_prec < next_prec) {
            rhs = parse_bin_op_rhs(tok_prec + 1, &rhs);
            if (!rhs) return NULL;
        }

        binaryExprAST LHS = {EXPR_BINARY, bin_op, lhs, rhs}; 
        lhs = &LHS;
    }
}
#include "ast.h"
#define MAX 1024
#define MAX_CHARS 256

static int BinopPrecedence[MAX_CHARS];
exprAST* parse_number_expr();
exprAST* parse_paren_expr();
exprAST* parse_ident_expr();
exprAST* parse_primary();
int get_tok_precedence();
exprAST* parse_expression();
exprAST* parse_bin_op_rhs(int expr_prec, exprAST* lhs);
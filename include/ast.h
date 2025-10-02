typedef enum {
    EXPR_NUMBER,
    EXPR_VARIABLE,
    EXPR_BINARY,
    EXPR_CALL
} ExprKind;

typedef struct exprAST {
    ExprKind kind;
} exprAST;

typedef struct {
    exprAST base; 
    double val;
} numberExprAST;

typedef struct {
    exprAST base;
    char *name;
} variableExprAST;

typedef struct {
    exprAST base;
    char op;
    exprAST *lhs;
    exprAST *rhs;
} binaryExprAST;

typedef struct {
    exprAST base;
    char *callee;
    exprAST **args;
    int argCount;
} callExprAST;

typedef struct {
    char *name;
    char **args;
    int argCount;
} prototypeAST;

typedef struct {
    prototypeAST *proto;
    exprAST *body;
} functionAST;

static int cur_tok;
static int get_next_tok();

exprAST* log_error(char *str);
prototypeAST* log_error_p(char *str);
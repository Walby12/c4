// include guard begin
#ifndef AST_H
#define AST_H


typedef enum {
    AST_NUMBER,
    AST_VARIABLE,
    AST_BINARY
} ASTNodeType;

typedef struct ASTNode {
    ASTNodeType type;
    union {
        struct { double value; } number;
        struct { char *name; } variable;
        struct { char op; struct ASTNode *lhs, *rhs; } binary;
    } data;
} ASTNode;

typedef struct {
    char *name;
    char **arg_names;
    char **arg_types;
    int arg_count;
    char *return_type;
} Prototype;

typedef struct {
    Prototype *proto;
    ASTNode *body;
} Function;

extern int cur_tok;
int get_next_tok();

#endif // AST_H
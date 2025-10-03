#include <stdio.h>
#define NOB_IMPLEMENTATION
#define NOB_STRIP_PREFIX
#include "nob.h"

typedef enum {
    STMT_PRINTLN,
    STMT_RETURN
} Stmt_Kind;

typedef struct Stmt Stmt;

struct Stmt {
    Stmt_Kind kind;
    union {
        struct { const char *message; };
        struct { int code; };
    };
};

typedef struct {
    Stmt **items;
    size_t count;
    size_t capacity;
} Stmt_List;

Stmt_List body = {0};

Stmt* stmt_println(const char *msg) {
    Stmt *stmt =  malloc(sizeof(*stmt));
    stmt->kind = STMT_PRINTLN;
    stmt->message = msg;
    return stmt;
}

Stmt* stmt_return(int code) {
    Stmt *stmt =  malloc(sizeof(*stmt));
    stmt->kind = STMT_RETURN;
    stmt->code = code;
    return stmt;
}

void eval_stmt(Stmt *stmt) {
    switch (stmt->kind) {
    case STMT_PRINTLN:
        printf("%s\n", stmt->message);
        break;
    case STMT_RETURN:
        exit(stmt->code);
    default:
        break;
    }
}

void yyerror(char const *s) {
    printf("yyerror: %s\n", s);
}

int yylex(void);

#include "parse.tab.c"
#include "lex.yy.c"

int yywrap() {
    return 1;
}

int main() {
    yyparse();
    return 0;
}
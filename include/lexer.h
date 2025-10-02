typedef enum {
    TOK_EOF,
    TOK_DEF,
    TOK_EXTERN,
    TOK_IDENT,
    TOK_NUMBER,
} TokensType;

extern char ident_str[256];
extern double num_val;
TokensType get_tok();
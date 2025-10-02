typedef enum {
    TOK_EOF,
    TOK_DEF,
    TOK_EXTERN,
    TOK_IDENT,
    TOK_NUMBER,
} TokensType;

static char *ident_str;
static double num_val;
TokensType get_tok();
%union {
    char *s_value;
    int i_value;
    Stmt *stmt_value;
    Stmt_List stmt_list_value;
}
%token  RETURN
%token  <i_value> NUMBER
%token  <s_value> ID
%token  OPAREN
%token  CPAREN
%token  OCURLY
%token  CCURLY
%token  SEMICOLON
%token  <s_value> STR
%token  RET_TYPE
%type   <stmt_value> stmt
%type   <stmt_list_value> stmt_list

%%
main: ID ID OPAREN CPAREN RET_TYPE ID OCURLY stmt_list CCURLY
    {
        for (size_t i = body.count; i > 0; --i) {
            eval_stmt(body.items[i - 1]);
        }
    }
stmt_list: /* empty */ { }
    | stmt SEMICOLON stmt_list 
    {
        da_append(&body, $1);
    }
stmt: ID OPAREN STR CPAREN 
    {
        if (strcmp($1, "println") == 0) {
            $$ = stmt_println($3);
        } else {
            printf("ERROR: unknown func: %s\n", $1);
            abort(); // TODO: fuck you
        }
    }
    | RETURN NUMBER 
    {
        $$ = stmt_return($2);
    }
%%

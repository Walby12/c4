DIGIT [0-9]
ID [a-z][a-z0-9]*

%%
[" "\n] {}

return { 
    return(RETURN); 
}

{DIGIT}+ {
    yylval.i_value = atoi(yytext);
    return(NUMBER);
}

{ID} {
    yylval.s_value = strdup(yytext);
    return(ID);
}

"(" {
    return(OPAREN);
}

")" {
    return(CPAREN);
}

"{" {
    return(OCURLY);
}

"}" {
    return(CCURLY);
}

";" {
    return(SEMICOLON);
}

"\"".*"\"" {
    yylval.s_value = strndup(yytext + 1, strlen(yytext) - 2);
    return(STR);
}

"@" {
    return(RET_TYPE);
}

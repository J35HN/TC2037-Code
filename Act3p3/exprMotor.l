%{

%}

%%
.* {fprintf(yyout, "char ");fprintf(yyout, yytext);fprintf(yyout, "\n");}
%%
int yywrap(void){
    return 1;
}
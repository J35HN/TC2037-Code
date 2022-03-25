%{

%}

%%
"int" {fprintf(yyout, "PR_int ");fprintf(yyout, yytext);fprintf(yyout, "\n");}
"float" {fprintf(yyout, "PR_float ");fprintf(yyout, yytext);fprintf(yyout, "\n");}
"string" {fprintf(yyout, "PR_string ");fprintf(yyout, yytext);fprintf(yyout, "\n");}
"bool" {fprintf(yyout, "PR_bool ");fprintf(yyout, yytext);fprintf(yyout, "\n");}
"if" {fprintf(yyout, "PR_if ");fprintf(yyout, yytext);fprintf(yyout, "\n");}
"True"|"False" {fprintf(yyout, "bool_Py ");fprintf(yyout, yytext);fprintf(yyout, "\n");}
"true"|"false" {fprintf(yyout, "bool_CppCj ");fprintf(yyout, yytext);fprintf(yyout, "\n");}
"+" {fprintf(yyout, "Mas ");fprintf(yyout, yytext);fprintf(yyout, "\n");}
"-" {fprintf(yyout, "Menos ");fprintf(yyout, yytext);fprintf(yyout, "\n");}
"*" {fprintf(yyout, "Multiplicacion ");fprintf(yyout, yytext);fprintf(yyout, "\n");}
"/" {fprintf(yyout, "Division ");fprintf(yyout, yytext);fprintf(yyout, "\n");}
"<=" {fprintf(yyout, "Menos_Que_Igual ");fprintf(yyout, yytext);fprintf(yyout, "\n");}
"<" {fprintf(yyout, "Menos_Que ");fprintf(yyout, yytext);fprintf(yyout, "\n");}
">=" {fprintf(yyout, "Mas_Que_Igual ");fprintf(yyout, yytext);fprintf(yyout, "\n");}
">" {fprintf(yyout, "Mas_Que ");fprintf(yyout, yytext);fprintf(yyout, "\n");}
"==" {fprintf(yyout, "Igual_Que_PyCpp ");fprintf(yyout, yytext);fprintf(yyout, "\n");}
"(=" {fprintf(yyout, "Igual_Que_Cj ");fprintf(yyout, yytext);fprintf(yyout, "\n");}
"=" {fprintf(yyout, "Asignacion_PyCpp ");fprintf(yyout, yytext);fprintf(yyout, "\n");}
"(" {fprintf(yyout, "Parentesis_abierto ");fprintf(yyout, yytext);fprintf(yyout, "\n");}
")" {fprintf(yyout, "Parentesis_cerrado ");fprintf(yyout, yytext);fprintf(yyout, "\n");}
([0-9]|[1-9]*)+"."[0-9]*(["e"|"E"]("+"|"-")?[0-9]*)? {fprintf(yyout, "double/float ");fprintf(yyout, yytext);fprintf(yyout, "\n");}
[1-9][0-9]* {fprintf(yyout, "Entero ");fprintf(yyout, yytext);fprintf(yyout, "\n");}
[a-zA-Z]("_"|[0-9]|[a-zA-Z])* {fprintf(yyout, "Variable_PyCpp ");fprintf(yyout, yytext);fprintf(yyout, "\n");}
[a-zA-Z]|"_"("_"|[0-9]|[a-zA-Z])* {fprintf(yyout, "Variable_Cj ");fprintf(yyout, yytext);fprintf(yyout, "\n");}
[ \t\n]+ /* nada */
. {fprintf(yyout, "No_Reconocido ");fprintf(yyout, yytext);fprintf(yyout, "\n");}
%%
int yywrap(void){
    return 1;
}
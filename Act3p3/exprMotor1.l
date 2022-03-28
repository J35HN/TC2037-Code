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
"+" {fprintf(yyout, "Plus ");fprintf(yyout, yytext);fprintf(yyout, "\n");}
"-" {fprintf(yyout, "Minus ");fprintf(yyout, yytext);fprintf(yyout, "\n");}
"*" {fprintf(yyout, "Multiplicacion ");fprintf(yyout, yytext);fprintf(yyout, "\n");}
"/" {fprintf(yyout, "Division ");fprintf(yyout, yytext);fprintf(yyout, "\n");}
"<=" {fprintf(yyout, "Less_Equal_Than ");fprintf(yyout, yytext);fprintf(yyout, "\n");}
"<" {fprintf(yyout, "Less_Than ");fprintf(yyout, yytext);fprintf(yyout, "\n");}
">=" {fprintf(yyout, "More_Equal_Than ");fprintf(yyout, yytext);fprintf(yyout, "\n");}
">" {fprintf(yyout, "More_Than ");fprintf(yyout, yytext);fprintf(yyout, "\n");}
"==" {fprintf(yyout, "Equal_To_PyCpp ");fprintf(yyout, yytext);fprintf(yyout, "\n");}
"(=" {fprintf(yyout, "Equal_To_Cj ");fprintf(yyout, yytext);fprintf(yyout, "\n");}
"=" {fprintf(yyout, "Assignation_PyCpp ");fprintf(yyout, yytext);fprintf(yyout, "\n");}
"(" {fprintf(yyout, "Open_Parentheses ");fprintf(yyout, yytext);fprintf(yyout, "\n");}
")" {fprintf(yyout, "Closed_Parentheses ");fprintf(yyout, yytext);fprintf(yyout, "\n");}
([0-9]|[1-9]*)+"."[0-9]*(["e"|"E"]("+"|"-")?[0-9]*)? {fprintf(yyout, "double/float ");fprintf(yyout, yytext);fprintf(yyout, "\n");}
[1-9][0-9]* {fprintf(yyout, "Integer ");fprintf(yyout, yytext);fprintf(yyout, "\n");}
[a-zA-Z]("_"|[0-9]|[a-zA-Z])* {fprintf(yyout, "Variable_PyCpp ");fprintf(yyout, yytext);fprintf(yyout, "\n");}
[a-zA-Z]|"_"("_"|[0-9]|[a-zA-Z])* {fprintf(yyout, "Variable_Cj ");fprintf(yyout, yytext);fprintf(yyout, "\n");}
. {fprintf(yyout, "validChar ");fprintf(yyout, yytext);fprintf(yyout, "\n");}
%%
int yywrap(void){return 1;}
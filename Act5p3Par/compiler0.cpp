#include <iostream>
#include <stdlib.h>
#include <stdio.h>

extern int yylex();
extern int yylineno;
extern char* yytext;

int main(){
	extern FILE *yyin, *yyout;
	yyin = fopen("./inputs_text/otherCode.txt", "r");
	yyout = fopen("outputTokens0.txt", "w");
	yylex();
	return 0;
}
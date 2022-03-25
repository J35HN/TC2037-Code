/*
Activity 3.3 - Syntax Highlighter
- Programing a basic syntax highlighter using Flex and HTML.
Author:
- Jeshua Nava Avila | A01639282
Date of creation and last modification:
- 03/23/2022
- 03/XX/2022
*/
#include <iostream>
#include <stdlib.h>
#include <stdio.h>

extern int yylex();
extern int yylineno;
extern char* yytext;

int main(){
    extern FILE *yyin, *yyout;
    yyin = fopen("inputText.txt", "r");
    yyout = fopen("outputTokens.txt", "w");
    yylex();
    return 0;
}
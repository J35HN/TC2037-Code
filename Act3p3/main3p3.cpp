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
#include <fstream>
#include <stdlib.h>
#include <stdio.h>
// Global variables
std::vector<std::string> tokensType;
/**
 * @brief Creates a Flex file for our regex motor.
 * 
 * @param path Where the .txt file is located (with the regex).
 */
void createFlexFile(std::string path){
    // Create and open file exprMoto.l
    std::ofstream myFile("exprMoto1.l");
    myFile << "%{\n\n%}\n\n%%\n";
    // Insert our regular expressions.
    myFile << "Funciono\n";
    myFile << "%%\nint yywrap(void){return 1;}";
    myFile.close();
}

int main(){
    //createFlexFile("Hola");
    return 0;
}
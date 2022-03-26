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
#include <vector>
// Global variables
std::vector<std::string> regExpressions;
std::vector<std::string> tokensTypeName;
/**
 * @brief Creates a Flex file for our re-gex motor.
 * 
 * @param path Where the .txt file is located (with the re-gex).
 */
void createFlexFile(std::string path){
    int middlePointLine = 0;
    std::string re_gex;
    std::string tokenType;
    std::string line;
    // Create and open file exprMoto.l
    std::ofstream myFile("exprMoto1.l");
    myFile << "%{\n\n%}\n\n%%\n";
    // Insert our regular expressions.
    std::ifstream txtFile(path.c_str()); // Opens our re-gex file.
    while (getline(txtFile, line)){
        // Traverse line and finds the regular expression and its type.
        for (int i = 0; i < line.length(); i++){
            if (line[i] == ':'){
                middlePointLine = i;
                break;
            }
        }
        if (middlePointLine != 0){
            re_gex = line.substr(0, middlePointLine - 1);
            tokenType = line.substr(middlePointLine + 2, line.length()-1);
            //std::cout << re_gex << " {fprintf(yyout, \"" << tokenType << " \");fprintf(yyout, yytext);fprintf(yyout, \"\\n\");}" << std::endl;
            myFile << re_gex << " {fprintf(yyout, \"" << tokenType << " \");fprintf(yyout, yytext);fprintf(yyout, \"\\n\");}" << "\n";
        }
    }
    
    txtFile.close(); // Closes our re-gex file.
    myFile << "%%\nint yywrap(void){return 1;}";
    myFile.close();
}

int main(){
    createFlexFile("inputRegex.txt");
    return 0;
}
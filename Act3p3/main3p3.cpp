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
 * @brief Creates a Flex file for our reg-ex motor.
 * 
 * @param path Where the .txt file is located (with the reg-ex).
 */
void createFlexFile(std::string path){
    int middlePointLine = 0;
    std::string reg_ex;
    std::string tokenType;
    std::string line;
    // Create and open file exprMoto.l
    std::ofstream myFile("exprMoto1.l");
    myFile << "%{\n\n%}\n\n%%\n";
    // Insert our regular expressions.
    std::ifstream txtFile(path.c_str()); // Opens our reg-ex file.
    while (getline(txtFile, line)){
        // Traverse line and finds the regular expression and its type.
        for (int i = 0; i < line.length(); i++){
            if (line[i] == ':'){
                middlePointLine = i;
                break;
            }
        }
        if (middlePointLine != 0){
            reg_ex = line.substr(0, middlePointLine - 1);
            tokenType = line.substr(middlePointLine + 2, line.length()-1);
            //std::cout << re_gex << " {fprintf(yyout, \"" << tokenType << " \");fprintf(yyout, yytext);fprintf(yyout, \"\\n\");}" << std::endl;
            myFile << reg_ex << " {fprintf(yyout, \"" << tokenType << " \");fprintf(yyout, yytext);fprintf(yyout, \"\\n\");}" << "\n";
        }
    }
    
    txtFile.close(); // Closes our re-gex file.
    myFile << "%%\nint yywrap(void){return 1;}";
    myFile.close();
}
/**
 * @brief Creates a Cpp file so we can compile our Flex file. 
 * 
 */
void createCompilerCpp(){
    // Create and open file compiler1.cpp
    std::ofstream myFile("compiler1.cpp");
    // Insert all neccesary info.
    myFile << "#include <iostream>\n#include <stdlib.h>\n#include <stdio.h>\n\n";
    myFile << "extern int yylex();\nextern int yylineno;\nextern char* yytext;\n\n";
    myFile << "int main(){\n\textern FILE *yyin, *yyout;\n\t";
    myFile << "yyin = fopen(\"inputText.txt\", \"r\");\n\t";
    myFile << "yyout = fopen(\"outputTokens.txt\", \"w\");\n\t";
    myFile << "yylex();\n\treturn 0;\n}";
}

int main(){
    createFlexFile("inputRegex.txt");
    createCompilerCpp();
    return 0;
}
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
#include <cstring>
#include <windows.h>
// Global variables
std::vector<std::string> regExpressions;
std::vector<std::string> tokensTypeName;
/**
 * @brief Creates a Flex File that is our reg-ex motor.
 * 
 * @param inputRegex file from where we obtain our reg-ex. 
 * @param outputFile desired name for the file we are creating.
 */
void createFlexFile(std::string inputRegex, std::string outputFile){
    int middlePointLine = 0;
    std::string reg_ex;
    std::string tokenType;
    std::string line;
    // Create and open file exprMoto.l
    std::ofstream myFile(outputFile);
    myFile << "%{\n\n%}\n\n%%\n";
    // Insert our regular expressions.
    std::ifstream txtFile(inputRegex.c_str()); // Opens our reg-ex file.
    while (getline(txtFile, line)){
        // Traverse line and finds the regular expression and its type.
        for (int i = 0; i < line.length(); i++){
            if (line[i] == ':'){
                middlePointLine = i;
                break;
            }
        }
        // Seperate in strings our regular expression and its type.
        if (middlePointLine != 0){ // In case there was no ":" to avoid errors.
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
 * @brief Creates a Cpp file so we can "compile" our Flex file.
 * 
 * @param outputFile desired name for the file we are creating.
 * @param outputTxt file were we output our tokens.
 * @param inputTxt file we read and apply our reg-ex motor.
 */
void createCompilerCpp(std::string outputFile, std::string outputTxt, std::string inputTxt){
    // Create and open file compiler1.cpp
    std::ofstream myFile(outputFile);
    // Insert all neccesary info.
    myFile << "#include <iostream>\n#include <stdlib.h>\n#include <stdio.h>\n\n";
    myFile << "extern int yylex();\nextern int yylineno;\nextern char* yytext;\n\n";
    myFile << "int main(){\n\textern FILE *yyin, *yyout;\n\t";
    myFile << "yyin = fopen(\"" << inputTxt << "\", \"r\");\n\t";
    //myFile << "yyin = fopen(\"inputText.txt\", \"r\");\n\t";
    myFile << "yyout = fopen(\"" << outputTxt << "\", \"w\");\n\t";
    //myFile << "yyout = fopen(\"outputTokens.txt\", \"w\");\n\t";
    myFile << "yylex();\n\treturn 0;\n}";
    myFile.close();
}
/**
 * @brief Validates if both essential files exist in current folder.
 * 
 * @param file_flex Flex file that is our reg-ex motor.
 * @param file_cpp Cpp file that helps us "compile" our flex file.
 * @return true 
 * @return false 
 */
bool ifFiles_FlexAndCompilerExist(std::string file_flex, std::string file_cpp){
    std::ifstream fileFlx;
    std::ifstream fileComp;
    fileFlx.open(file_flex);
    fileComp.open(file_cpp);
    if (fileFlx && fileComp){
        fileFlx.close();
        fileComp.close();
        return true;
    }
    return false;
}
/**
 * @brief Validates if C file is created by the Flex file.
 * 
 * @param cFile file that should be created.
 * @return true 
 * @return false 
 */
bool ifFile_cExist(std::string cFile){
    std::ifstream file;
    file.open(cFile);
    if (file){
        file.close();
        return true;
    }
    return false;
}
/**
 * @brief System command to compile flex file.
 * 
 * @param flexFile flex file to compile.
 */
void compileFlexFile(std::string flexFile){
    char command[100];
    strcpy(command, "flex ");
    strcat(command, flexFile.c_str());
    // Compile Flex file.
    system(command);
}
/**
 * @brief System command to compile lex.yy.c file.
 * 
 * @param cFile c file to compile.
 * @param compiler file to compile with our cFile.
 */
void compileCFile(std::string cFile, std::string compiler){
    char command[100];
    strcpy(command, "g++ ");
    strcat(command, compiler.c_str());
    strcat(command, " ");
    strcat(command, cFile.c_str());
    strcat(command, " -o runForOutput");
    system(command);
}
/**
 * @brief Opens temp.exe file created by compiling our compiler.cpp
 * 
 */
void open_tempFile(){
    char command[100];
    strcpy(command, "runForOutput.exe");
    system(command);
}
int main(){
    // Definitions of files.
    std::string file_InputText = "inputText.txt";
    std::string file_InputRegEx = "inputRegex.txt";
    std::string file_regExMotor = "exprMotor1.l";
    std::string file_Compiler = "compiler1.cpp";
    std::string file_tokensOutput = "outputTokens.txt";
    // Creation of the Flex file and the Compiler file.
    createFlexFile(file_InputRegEx, file_regExMotor);
    createCompilerCpp(file_Compiler, file_tokensOutput, file_InputText);
    // Check if both files are created. If they do, continue with the execution of the program.
    if (ifFiles_FlexAndCompilerExist(file_regExMotor, file_Compiler)){
        compileFlexFile(file_regExMotor);
        // Check if C file exist.
        if (ifFile_cExist("lex.yy.c")){
            compileCFile("lex.yy.c", file_Compiler);
            open_tempFile();
        } else {
            std::cout << "Can not continue to execute the program, lex.yy.c file not created" << std::endl;
        }
    } else {
        std::cout << "Can not continue to execute the program, flex file or compiler file does not exist" << std::endl;
    }

    return 0;
}
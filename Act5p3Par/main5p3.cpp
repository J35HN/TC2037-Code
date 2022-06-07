/*
Activity 5.3 - Syntax Highlighter Parallel.
- Programing a basic syntax highlighter using Flex and HTML.
Author:
- Jeshua Nava Avila | A01639282
Date of creation and last modification:
- 06/04/2022
- 06/05/2022
*/
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <cstring>
#include <windows.h>
#include <unordered_map>
#include <sys/types.h>
#include <dirent.h>
#include <chrono>
#include <thread>
#include <cmath>
using namespace std::chrono;
// Global variables
int nTokenTypes = 25; // Modify to according number of token types (add or delete number of colors [CSS] to match this number).
std::vector<std::string> tokensTypeName;
std::vector<std::string> colors{"red", "fuchsia", "yellow", "blue", "aqua", "lime", "teal", "aliceblue", "brown", "bisque", "cyan", "darkorange", "deeppink", "peru", "plum", "springgreen", "tomato", "tan", "yellowgreen", "skyblue", "salmon", "pink", "gold", "magenta", "white"};
std::unordered_map<std::string, std::string> tokenTypeAndColor; 
std::vector<std::string> inputFiles;
// Definitions of files, paths and strings.
std::string file_InputRegEx = "inputRegex.txt";
std::string file_regExMotor = "exprMotor.l";
std::string directory_inputTexts = "./inputs_text";
std::string tokenType;
std::string color;

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
            tokensTypeName.push_back(tokenType);
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
    myFile << "yyout = fopen(\"" << outputTxt << "\", \"w\");\n\t";
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
void compileCFile(std::string cFile, std::string compiler, int numberOfThread){
    char command[100];
    std::string com = " -o runForOutput" + std::to_string(numberOfThread);
    const char *c = com.c_str();
    strcpy(command, "g++ ");
    strcat(command, compiler.c_str());
    strcat(command, " ");
    strcat(command, cFile.c_str());
    strcat(command, c);
    system(command);
}
/**
 * @brief Opens temp.exe file created by compiling our compiler.cpp
 * 
 */
void open_tempFile(int numberOfThread){
    char command[100];
    std::string com = "runForOutput" + std::to_string(numberOfThread) + ".exe";
    const char *c = com.c_str();
    strcpy(command, c);
    system(command);
}
/**
 * @brief Creates our HTML + CSS file.
 * 
 * @param inputFileTxt the input text for our syntax highlighter.
 * @param name of the HTML file.
 */
void createHTML(std::string inputFileTxt, std::string name){
    int middlePointLine = 0;
    std::string line;
    std::string token;
    std::string tokenType;
    std::string paragraph = "\t\t<p>";
    std::string formatP = "<span ";
    // Create and open file syntaxHi.html
    std::ofstream myFile(name + ".html");
    // Insert all neccesary info. from our outputTokenFile.
    myFile << "<!DOCTYPE html>";
    myFile << "<html>\n";
    myFile << "<head>\n\t<title> Syntax Highlighter by Jesh</title>\n";
    myFile << "\t<style type=\"text/css\">\n";
    myFile << "\t\tbody{background-color: #000000; color: #ffffff; font-family: Tahoma, Geneva, sans-serif; width:98%; margin: auto;}\n";
    myFile << "\t\tp{width: 95%; margin: auto; font-size:20px;}\n";
    myFile << "\t</style>\n";
    myFile << "</head>\n";
    myFile << "<body>\n";
    myFile << "\t<h1> Syntax Highlighter </h1>\n\t<h2> by Jeshua Nava Avila | A01639282 </h2>\n";
    myFile << "\t<div>\n";
    // Read  inputFileTxt.
    std::ifstream txtFile (inputFileTxt.c_str());
    while (getline(txtFile, line)){
        // If line is empty, we add our current paragraph, if not, we keep appending.
        if(line == ""){
            paragraph = paragraph + "</p>\n";
            myFile << paragraph;
            paragraph = "\t\t<p>"; // reset paragraph.
        } else {
            // Identify our token and out type of token. So we traverse our line and spot a space char.
            for (int i = 0; i < line.length(); i++){
                if (line[i] == ' '){
                    middlePointLine = i;
                break;
                }
            }
            // Define our token and tokenType.
            if (middlePointLine != 0){
                tokenType = line.substr(0 , middlePointLine);
                token = line.substr(middlePointLine + 1, line.length() - 1);
                formatP = formatP + "style=\"color: " + tokenTypeAndColor[tokenType] + "\">" + token + "</span>"; // Format our token to its color.
            }
            paragraph = paragraph + formatP;
            formatP = "<span ";
        }
    }
    // Append if paragaph has info.
    if (paragraph != "\t\t<p>"){
        myFile << paragraph;
        paragraph = "";
    }
    myFile << "\t</div>\n";
    myFile << "</body>\n";
    myFile << "</html>";
    myFile.close();
}
/**
 * @brief Function that analyzes text and creates HTML. This function is to be run by a single thread.
 * 
 * @param numberOfThread what thread is running this procces.
 * @param filesToAnalyze how many files this thread has to analyze.
 * @param step the group of files this thread is in charge of.
 */
void threadMain(int numberOfThread, int filesToAnalyze, int step){
    //std::cout << "\nThread: " << numberOfThread << ". Files: " << filesToAnalyze << " last? " << isLast << std::endl;
    std::string file_compiler = "compiler" + std::to_string(numberOfThread) + ".cpp";
    std::string file_tokensOutput = "outputTokens" + std::to_string(numberOfThread) + ".txt";
    std::string htmlName;
    // Definitions of starting and ending indexes.
    int start = numberOfThread * step;
    int end = 0;
    // Differentiate between the amount of files 
    if(filesToAnalyze == step){
        end = start + (step - 1);
    } else {
        end = start + (filesToAnalyze - 1);
    }
    // Analyze the following indexes:
    for (int i = start; i <= end; i++){
        htmlName = "SyntaxHi" + std::to_string(i);
        // Creation of the compiler file.
        createCompilerCpp(file_compiler, file_tokensOutput, inputFiles[i]);
        // Check if flex file and compiler are created.
        if (ifFiles_FlexAndCompilerExist(file_regExMotor, file_compiler)){
            compileFlexFile(file_regExMotor);
            // Check if C file exist.
            if (ifFile_cExist("lex.yy.c")){
                compileCFile("lex.yy.c", file_compiler, numberOfThread);
                open_tempFile(numberOfThread);
                createHTML(file_tokensOutput, htmlName);
            } else {
                std::cout << "Can not continue to execute the program, lex.yy.c file not created" << std::endl;
            }
        } else {
            std::cout << "Can not continue to execute the program, flex file or compiler file does not exist" << std::endl;
        }
    }
}

/**
 * @brief Inserts to vector "inputFiles" the names of the inputs files in the input directory.
 * 
 * @param path the path to our input directory.
 */
 void readAmountInputFiles(std::string path){
    const char *c = path.c_str(); // Convert string to const char*.
    // Read names of files from directory (no explanation, code is from internet).
    struct dirent *d;
    DIR *dr;
    dr = opendir(c);
    if (dr != NULL){
        for (d = readdir(dr); d != NULL; d = readdir(dr)){
            inputFiles.push_back(path + "/" + d -> d_name); // Insert to vector the name of the files.
        }
        closedir(dr);
    } else 
        // In case an error occurs, indicate it.
        std::cout << "\nError Occurred, couldn't read or open input files directory!\n";
    // Delete objects "." and ".." from vector; they are the first and second index.
    inputFiles.erase(inputFiles.begin(), inputFiles.begin()+2);
 }

int main(){
    // Measure Time.
    auto start = high_resolution_clock::now();
    // Define amount of threads. My computer has 12 threads (6 Cores * 2 threads per core). In this case, I will only use 2.
    // BE SURE THAT THE NUMBER OF THREADS ARE NOT GREATER THAN 12 NOR LESS THAN 1. 
    int number_threads = 2;
    // Definition of threads, and integers that will help the threads. 
    std::vector<std::thread> myThreads(number_threads);
    int step = 0;
    int dif = 0;
    // Read amount of files in directory "inputs_text".
    readAmountInputFiles(directory_inputTexts);
    // Creation of the Flex file.
    createFlexFile(file_InputRegEx, file_regExMotor);
    // Assign a color to a token type.
    for (int i = 0; i < nTokenTypes; i++){
        color = colors[i];
        tokenType = tokensTypeName[i];
        tokenTypeAndColor[tokenType] = color;
    }
    // If our amount of threads is greater or equal than the amount of input files, use the amount of threads neccesary.
    // Else, assign each thread an amount of input files.
    if (number_threads >= inputFiles.size()){
        // Execute threads.
        for (int i = 0; i < inputFiles.size(); i++){
            myThreads[i] = std::thread(threadMain, i, 1, 1);
        }
        // Wait and stop the threads.
        for (int i = 0; i < inputFiles.size(); i++){
            myThreads[i].join();
        }
    } else {
        // Determine how many files should a thread analyze.
        step = std::floor(inputFiles.size() / number_threads);
        // Execute threads.
        for (int i = 0; i < number_threads; i++){
            // Add the remaining input files that are no part of a step into the last thread.
            if (i == (number_threads-1)){
                dif = inputFiles.size() - (step * number_threads);
            }
            myThreads[i] = std::thread(threadMain, i, step + dif, step);
        }
        // Wait and stop the threads.
        for (int i = 0; i < number_threads; i++){
            myThreads[i].join();
        }
    }
    //calculate time
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    std::cout << "Time taken by program: " << duration.count() << " microseconds" << std::endl;
    return 0;
}
/*
Activity 3.2 - Programming a DFA
- Programing of a Lexer using a Deterministic Finite Automata.
Author:
- Jeshua Nava Avila | A01639282
Date of creation and last modification:
- 03/13/2022
- 03/14/2022
*/
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <unordered_map>
// Global variables
std::string archivetxt = "Prueba.txt";
std::string globalState = "";
std::string currentToken = "";
bool errorFound = false;
int numColumn = 1;
int numLine = 1;
std::vector<std::string> tokens;
std::vector<std::string> type;
// Map of inputs and its representation in this DFA
std::unordered_map<std::string, std::string> inputsEq({
    {" ", "Esp"},
    {"g","P"}, {"G","P"}, {"h","P"}, {"H","P"}, {"i","P"}, {"I","P"}, {"j","P"}, {"J","P"}, {"k","P"}, {"K","P"}, {"l","P"}, {"L","P"}, {"m","P"}, {"M","P"}, {"n","P"}, {"N","P"}, {"ñ","P"}, {"Ñ","P"}, {"o","P"}, {"O","P"}, 
    {"p","P"}, {"P","P"}, {"q","P"}, {"Q","P"}, {"r","P"}, {"R","P"}, {"s","P"}, {"S","P"}, {"t","P"}, {"T","P"}, {"u","P"}, {"U","P"}, {"v","P"}, {"V","P"}, {"w","P"}, {"W","P"}, {"y","P"}, {"Y","P"}, {"z","P"}, {"Z","P"},
    {"1","N"}, {"2","N"}, {"3","N"}, {"4","N"}, {"5","N"}, {"6","N"}, {"7","N"}, {"8","N"}, {"9","N"},
    {"_", "Und"},
    {"e","eE"}, {"E","eE"}, {"x","xX"}, {"X","xX"}, {"a","H"}, {"A","H"}, {"b","H"}, {"B","H"}, {"c","H"}, {"C","H"}, {"d","H"}, {"D","H"}, {"f","H"}, {"F","H"},
    {"0", "0"}, {".","."},
    {"-","-"}, {"/","/"}, {"(","("}, {")",")"},
    {"+","S"}, {"^","S"}, {"*","S"}, {"=","S"}});
/// Map for each state from the table of transition
std::unordered_map<std::string, std::string> q0({{"Esp", "q0"}, {"P","q1"}, {"N", "q2"}, {"Und", "q13"}, {"eE", "q1"}, {"xX", "q1"}, {"H", "q1"}, {"0", "q7"}, {".", "q6"}, {"-", "q12"}, {"/", "q12"}, {"(", "q14"}, {")", "q15"}, {"S", "q12"}});
std::unordered_map<std::string, std::string> q1({{"Esp", "q0"}, {"P","q1"}, {"N", "q1"}, {"Und", "q1"}, {"eE", "q1"}, {"xX", "q1"}, {"H", "q1"}, {"0", "q1"}, {".", "q13"}, {"-", "q12"}, {"/", "q12"}, {"(", "q14"}, {")", "q15"}, {"S", "q12"}});
std::unordered_map<std::string, std::string> q2({{"Esp", "q0"}, {"P","q13"}, {"N", "q2"}, {"Und", "q13"}, {"eE", "q5"}, {"xX", "q13"}, {"H", "q13"}, {"0", "q2"}, {".", "q3"}, {"-", "q12"}, {"/", "q12"}, {"(", "q14"}, {")", "q15"}, {"S", "q12"}});
std::unordered_map<std::string, std::string> q3({{"Esp", "q0"}, {"P","q13"}, {"N", "q3"}, {"Und", "q13"}, {"eE", "q5"}, {"xX", "q13"}, {"H", "q13"}, {"0", "q3"}, {".", "q13"}, {"-", "q12"}, {"/", "q12"}, {"(", "q14"}, {")", "q15"}, {"S", "q12"}});
std::unordered_map<std::string, std::string> q4({{"Esp", "q0"}, {"P","q13"}, {"N", "q4"}, {"Und", "q13"}, {"eE", "q13"}, {"xX", "q13"}, {"H", "q13"}, {"0", "q4"}, {".", "q13"}, {"-", "q12"}, {"/", "q12"}, {"(", "q14"}, {")", "q15"}, {"S", "q12"}});
std::unordered_map<std::string, std::string> q5({{"Esp", "q13"}, {"P","q13"}, {"N", "q4"}, {"Und", "q13"}, {"eE", "q13"}, {"xX", "q13"}, {"H", "q13"}, {"0", "q4"}, {".", "q13"}, {"-", "q4"}, {"/", "q13"}, {"(", "q13"}, {")", "q13"}, {"S", "q13"}});
std::unordered_map<std::string, std::string> q6({{"Esp", "q13"}, {"P","q13"}, {"N", "q3"}, {"Und", "q13"}, {"eE", "q13"}, {"xX", "q13"}, {"H", "q13"}, {"0", "q3"}, {".", "q13"}, {"-", "q13"}, {"/", "q13"}, {"(", "q13"}, {")", "q13"}, {"S", "q13"}});
std::unordered_map<std::string, std::string> q7({{"Esp", "q13"}, {"P","q13"}, {"N", "q8"}, {"Und", "q13"}, {"eE", "q13"}, {"xX", "q9"}, {"H", "q13"}, {"0", "q13"}, {".", "q6"}, {"-", "q12"}, {"/", "q12"}, {"(", "q14"}, {")", "q15"}, {"S", "q12"}});
std::unordered_map<std::string, std::string> q8({{"Esp", "q0"}, {"P","q13"}, {"N", "q8"}, {"Und", "q13"}, {"eE", "q13"}, {"xX", "q13"}, {"H", "q13"}, {"0", "q8"}, {".", "q13"}, {"-", "q12"}, {"/", "q12"}, {"(", "q14"}, {")", "q15"}, {"S", "q12"}});
std::unordered_map<std::string, std::string> q9({{"Esp", "q13"}, {"P","q13"}, {"N", "q10"}, {"Und", "q13"}, {"eE", "q10"}, {"xX", "q13"}, {"H", "q10"}, {"0", "q10"}, {".", "q13"}, {"-", "q13"}, {"/", "q13"}, {"(", "q13"}, {")", "q13"}, {"S", "q13"}});
std::unordered_map<std::string, std::string> q10({{"Esp", "q0"}, {"P","q13"}, {"N", "q10"}, {"Und", "q13"}, {"eE", "q10"}, {"xX", "q13"}, {"H", "q10"}, {"0", "q10"}, {".", "q13"}, {"-", "q12"}, {"/", "q12"}, {"(", "q14"}, {")", "q15"}, {"S", "q12"}});
std::unordered_map<std::string, std::string> q11({{"Esp", "q11"}, {"P","q11"}, {"N", "q11"}, {"Und", "q11"}, {"eE", "q11"}, {"xX", "q11"}, {"H", "q11"}, {"0", "q11"}, {".", "q11"}, {"-", "q11"}, {"/", "q11"}, {"(", "q11"}, {")", "q11"}, {"S", "q11"}});
std::unordered_map<std::string, std::string> q12({{"Esp", "q12"}, {"P","q1"}, {"N", "q2"}, {"Und", "q13"}, {"eE", "q1"}, {"xX", "q1"}, {"H", "q1"}, {"0", "q7"}, {".", "q6"}, {"-", "q13"}, {"/", "q11"}, {"(", "q14"}, {")", "q13"}, {"S", "q13"}});
std::unordered_map<std::string, std::string> q13({{"Esp", "q13"}, {"P","q13"}, {"N", "q13"}, {"Und", "q13"}, {"eE", "q13"}, {"xX", "q13"}, {"H", "q13"}, {"0", "q13"}, {".", "q13"}, {"-", "q13"}, {"/", "q13"}, {"(", "q13"}, {")", "q13"}, {"S", "q13"}});
std::unordered_map<std::string, std::string> q14({{"Esp", "q14"}, {"P","q1"}, {"N", "q2"}, {"Und", "q13"}, {"eE", "q1"}, {"xX", "q1"}, {"H", "q1"}, {"0", "q7"}, {".", "q6"}, {"-", "q12"}, {"/", "q13"}, {"(", "q14"}, {")", "q15"}, {"S", "q13"}});
std::unordered_map<std::string, std::string> q15({{"Esp", "q15"}, {"P","q1"}, {"N", "q1"}, {"Und", "q13"}, {"eE", "q1"}, {"xX", "q1"}, {"H", "q1"}, {"0", "q7"}, {".", "q13"}, {"-", "q12"}, {"/", "q12"}, {"(", "q14"}, {")", "q15"}, {"S", "q12"}});
/**
 * @brief Prints the contents of a vector.
 * @param vector Vector which we print each element.
 */
void printTable(std::vector<std::string> vecToken, std::vector<std::string> vecType){
    int numSpaces = 0;
    // Find largest element (according to size).
    for (int i=0; i < vecToken.size(); i++){ if (vecToken[i].size() > numSpaces){numSpaces = vecToken[i].size();}}
    numSpaces += 5; // So we can have seperation in the table.
    // Print the first half.
    for (int i=0; i < numSpaces; i++){std::cout << "-";}
    std::cout << "-------------------------------------------------" << std::endl;
    std::cout << "| Token";
    for (int i=0; i < (numSpaces - 6); i++){
        std::cout << " ";
    }
    std::cout << " | Tipo                                        |" << std::endl;
    for (int i=0; i < numSpaces; i++){std::cout << "-";}
    std::cout << "-------------------------------------------------" << std::endl;
    for (int i=0; i < vecToken.size(); i++){
        std::cout << "| " << vecToken[i];
        for (int e=0; e < (numSpaces - vecToken[i].size()); e++){
            std::cout << " ";
        }
        std::cout << "| " << vecType[i];
        for (int e=0; e < (44 - vecType[i].size()); e++){
            std::cout << " ";
        }
        std::cout << "|" << std::endl;
    }
    for (int i=0; i < numSpaces; i++){std::cout << "-";}
    std::cout << "-------------------------------------------------" << std::endl;
}
/**
 * @brief Give the state depending what is the input, according to the transition table.
 * 
 * @param state State in which the DFA finds itself.
 * @param str Input that will determine the next state.
 * @return std::string , New State of the DFA.
 */
std::string obtainNewState(std::string state, std::string str){
    str = inputsEq[str]; // Convert our str to its representation according to our Transition Table.
    if (state == "q0"){ return q0[str]; } 
    else if (state == "q1"){ return q1[str];} 
    else if (state == "q2"){ return q2[str];} 
    else if (state == "q3"){ return q3[str];} 
    else if (state == "q4"){ return q4[str];} 
    else if (state == "q5"){ return q5[str];} 
    else if (state == "q6"){ return q6[str];} 
    else if (state == "q7"){ return q7[str];} 
    else if (state == "q8"){ return q8[str];} 
    else if (state == "q9"){ return q9[str];} 
    else if (state == "q10"){ return q10[str];} 
    else if (state == "q11"){ return q11[str];} 
    else if (state == "q12"){ return q12[str];} 
    else if (state == "q13"){ return q13[str];} 
    else if (state == "q14"){ return q14[str];} 
    else if (state == "q15"){ return q15[str];}
    return "Error";
}
/**
 * @brief Recursive function for the Extended Transition Function of a DFA.
 * 
 * @param state The state in which the function finds itself.
 * @param str The string or "char" that will determine the next state.
 */
std::string extendedTranFunc(std::string state, std::string str){
    if (errorFound == true){return "";} // Stop if we have an error.
    if (globalState == "q13") { // Check if we have an error.
        tokens.push_back(currentToken);
        std::string errorMsg = "Error en Linea ";
        errorMsg += std::to_string(numLine); 
        errorMsg += ", empieza en Columna ";
        errorMsg += std::to_string(numColumn-1);
        type.push_back(errorMsg); 
        errorFound = true;
        return "";
    }
    std::string stateQ = "";
    std::string newState = "";
    if (str.size() > 1){ // If it is, we need to break this string in two, and apply our Extended Transition Function.
        std::string stateQ = str.substr(0, str.size()-1); // We grab w.
        std::string subStr = str.substr(str.size()-1, str.size()-1); // We grab sigma.
        globalState = extendedTranFunc(state, stateQ); // Obtain new state.
        return extendedTranFunc(globalState, subStr); // Recursively traverse the string.
    }
    stateQ = str;
    globalState = obtainNewState(state, stateQ); // Obtain our new state.
    // Depending from which state we changed, we can confirm if we have a valid token.
    if (globalState == "q0" && state == "q1"){ tokens.push_back(currentToken); type.push_back("Variable"); currentToken = "";}
    else if (globalState == "q0" && state == "q2"){ tokens.push_back(currentToken); type.push_back("Entero"); currentToken = "";}
    else if (globalState == "q0" && state == "q3"){ tokens.push_back(currentToken); type.push_back("Real"); currentToken = "";}
    else if (globalState == "q0" && state == "q4"){ tokens.push_back(currentToken); type.push_back("Real"); currentToken = "";}
    else if (globalState == "q0" && state == "q8"){ tokens.push_back(currentToken); type.push_back("Octal"); currentToken = "";}
    else if (globalState == "q0" && state == "q10"){ tokens.push_back(currentToken); type.push_back("Hexadecimal"); currentToken = "";}
    else if (globalState == "q12" || globalState == "q14" || globalState == "q15"){
        // Before having an operator in currentToken, if we have "chars" in currentToken, we need to add it to our vector.
        if (currentToken.size() > 0) {
            // We check what kind of type it is according to our last (or current) state.
            if (state == "q1"){ tokens.push_back(currentToken); type.push_back("Variable"); currentToken = "";}
            else if (state == "q2"){ tokens.push_back(currentToken); type.push_back("Entero"); currentToken = "";}
            else if (state == "q3" || state == "q4" || state == "q5") { tokens.push_back(currentToken); type.push_back("Real"); currentToken = "";}
            else if (state == "q7"){ tokens.push_back(currentToken); type.push_back("Entero"); currentToken = "";}
            else if (state == "q8"){ tokens.push_back(currentToken); type.push_back("Octal"); currentToken = "";}
            else if (state == "q10"){ tokens.push_back(currentToken); type.push_back("Hexadecimal"); currentToken = "";}
        }
    }
    //std::cout << currentToken << ":" << state << std::endl;
    if (state == "q12" || state == "q14" || state == "q15"){
        // We check what kind of operator we have.
        if (currentToken == "/" && globalState != "q11"){ // Means we our not in a comment.
            tokens.push_back(currentToken); type.push_back("Division"); currentToken = "";
        } else if (currentToken == "-"){
            tokens.push_back(currentToken); type.push_back("Resta o Negativo"); currentToken ="";
        } else if (currentToken == "+"){
            tokens.push_back(currentToken); type.push_back("Suma"); currentToken ="";
        } else if (currentToken == "*"){
            tokens.push_back(currentToken); type.push_back("Multiplicacion"); currentToken ="";
        } else if (currentToken == "^"){
            tokens.push_back(currentToken); type.push_back("Potencia"); currentToken ="";
        } else if (currentToken == "="){
            tokens.push_back(currentToken); type.push_back("Asignacion"); currentToken ="";
        } else if (currentToken == "("){
            tokens.push_back(currentToken); type.push_back("Parentesis que abre"); currentToken ="";
        } else if (currentToken == ")"){
            tokens.push_back(currentToken); type.push_back("Parentesis que cierra"); currentToken ="";
        }
    }
    
    // Concatenate our current "char" to our token, so we could add it later to our vector of tokens.
    if (str != " "){ // we don't concatenate if str is a space.
        currentToken += str;
    } else if (globalState == "q11" && state == "q11"){
        currentToken += str;
    }
    numColumn++; //Increment by one our line.
    return globalState;
}

/**
 * @brief Function that reads an archive with the DFA Lexer, and prints the corresponding tokens.
 * @param archivo Archive to read.
 */
void lexerAritmetico(std::string archivo){
    std::string lastState = "q0";
    std::string line;
    std::ifstream openArchivo(archivo.c_str()); // Open archive.
    // Read archivo and store each line in LinesArchivo.
    while (getline(openArchivo, line)) {
        if (errorFound == true) {break;}
        lastState = extendedTranFunc("q0", line);
        // Check if we have a token in currentToken.
        if (currentToken.size() > 0){
            if (lastState == "q11"){
                tokens.push_back(currentToken);
                type.push_back("Comentario");
                currentToken = "";
            } else if (lastState == "q0"){ currentToken = "";}
            else if (lastState == "q1"){ tokens.push_back(currentToken); type.push_back("Variable");}
            else if (lastState == "q2"){ tokens.push_back(currentToken); type.push_back("Entero");}
            else if (lastState == "q3" || lastState == "q4"){ tokens.push_back(currentToken); type.push_back("Real");}
            else if (lastState == "q8"){ tokens.push_back(currentToken); type.push_back("Octal");}
            else if (lastState == "q10"){ tokens.push_back(currentToken); type.push_back("Hexadecimal");}
            else if (lastState == "q14"){ tokens.push_back(currentToken); type.push_back("Parentesis que abre");}
            else if (lastState == "q15"){ tokens.push_back(currentToken); type.push_back("Parentesis que cierra");}
            else {
                errorFound = true;
                tokens.push_back(currentToken);
                std::string errorMsg = "Error en Linea ";
                errorMsg += std::to_string(numLine); 
                errorMsg += ", empieza en Columna ";
                errorMsg += std::to_string(numColumn-1);
                type.push_back(errorMsg);
            }
            currentToken = "";
        }
        numLine++; // Increment by one our Line.
        numColumn = 1; // Reset our column counter.
    }
    openArchivo.close(); // Close archive.
    printTable(tokens, type);
}

int main(){
    lexerAritmetico(archivetxt);
    return 0;
}
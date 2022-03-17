                    tokens.push_back(currentToken);
                    std::string errorMsg = "Error en Linea ";
                    errorMsg += std::to_string(numLine); 
                    errorMsg += ", Columna ";
                    errorMsg += std::to_string(numColumn-1);
                    type.push_back(errorMsg);
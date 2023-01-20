#include "Logger.h"

#include <iostream>
#include <sstream>
#include <filesystem>
#include <fstream>


template <typename varType>
Logger& Logger::operator << (varType const & value){
    if (logLevel == DEBUG && !outputDebugs){
        return *this;
    }

    std::ostringstream buffer;
    if (outputLevelTag){
        if (logLevel == ERROR){
            buffer << "[ERROR] ";
        }else if (logLevel == WARNING){
            buffer << "[WARNING] ";
        }else if (logLevel == INFO){
            buffer << "[INFO] ";
        }else if (logLevel == DEBUG){
            buffer << "[DEBUG] ";
        }
    }

    buffer << value;
    if (outputToConsole){
        if (logLevel == ERROR){
            std::cerr << buffer.str() << std::flush;
        }else{
            std::cout << buffer.str();
        }
    }

    if (outputToFile){
        std::filesystem::create_directory(logDirectoryName);
        std::ofstream logFile;
        logFile.open(logDirectoryName + "/" + logFileName, std::ios::app);
        logFile << buffer.str();
        logFile.close();
    }

    return *this;
}

void Logger::delete_log_file(){
    std::filesystem::remove(logDirectoryName + "/" + logFileName);
}

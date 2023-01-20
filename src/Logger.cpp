#include "Logger.h"

void Logger::output(std::string const & value){
    if (logLevel == DEBUG && !outputDebugs){
        return;
    }

    if (outputToConsole){
        if (logLevel == ERROR){
            std::cerr << value << std::flush;
        }else{
            std::cout << value;
        }
    }

    if (outputToFile){
        std::filesystem::create_directory(logDirectoryName);
        std::ofstream logFile;
        logFile.open(logDirectoryName + "/" + logFileName, std::ios::app);
        logFile << value;
        logFile.close();
    }
}

void Logger::delete_log_file(){
    std::filesystem::remove(logDirectoryName + "/" + logFileName);
}

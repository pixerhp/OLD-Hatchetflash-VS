#pragma once

#include <iostream>
#include <string>
#include <sstream>
#include <filesystem>
#include <fstream>

class Logger{
public:
    enum LogLevel{ERROR, WARNING, INFO, DEBUG};
private:
    LogLevel logLevel = INFO;

    Logger() {} // Private to prevent existance of multiple Loggers.
    Logger(const Logger&) {} // A private copy constructor who's purpose is to prevent multiple copies of the singleton instance from existing.

    #ifndef NDEBUG
		const bool outputDebugs = true;
	#else
		const bool outputDebugs = false;
	#endif

    void output(std::string const & value);
public:
    bool outputToFile = true;
    bool outputToConsole = true;

    std::string logDirectoryName = "logs";
    std::string logFileName = "log.txt";

    static Logger& getInstance(){
        static Logger instance;
        instance.logLevel = INFO;
        return instance;
    }

    template <typename varType>
    Logger& operator<< (varType const & value){
        std::ostringstream buffer;

        buffer << value;

        output(buffer.str());

        return *this;
    }

    Logger& operator<< (LogLevel const & value){
        if (value == ERROR){
            output("[ERROR] ");
        }else if (value == WARNING){
            output("[WARNING] ");
        }else if (value == INFO){
            output("[INFO] ");
        }else if (value == DEBUG){
           output("[DEBUG] ");
        }

        logLevel = value;

        return *this;
    }

    void delete_log_file();
};

#pragma once

class Logger{
private:
    Logger() {} // Private to prevent existance of multiple Loggers.
    Logger(const Logger&) {} // A private copy constructor who's purpose is to prevent multiple copies of the singleton instance from existing.

    #ifndef NDEBUG
		const bool outputDebugs = true;
	#else
		const bool outputDebugs = false;
	#endif
public:
    enum LogLevel{ERROR, WARNING, INFO, DEBUG};

    LogLevel logLevel = INFO;

    bool outputToFile = true;
    bool outputToConsole = true;
    bool outputLevelTag = true;

    std::string logDirectoryName = "logs";
    std::string logFileName = "log.txt";

    static Logger& getInstance(){
        static Logger instance;
        return instance;
    }

    template <typename varType>
    Logger& operator << (varType const & value);

    void delete_log_file();
};

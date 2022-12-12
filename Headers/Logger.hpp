#pragma once

#include <iostream>
#include <sstream>
#include <fstream>
#include <filesystem>

namespace Logger{
	enum LogLevel{ERROR,WARNING,INFO,DEBUG};
	#ifndef NDEBUG
		const LogLevel logMode=DEBUG;
	#else
		const LogLevel logMode=INFO;
	#endif
	class Log{
		public:
		Log(LogLevel logLevel=INFO){
			currentLogLevel=logLevel;
			if(currentLogLevel<=logMode){
				switch (currentLogLevel)
				{
					case ERROR:{
						buffer << "[ERROR] ";
						break;
					}
					
					case WARNING:{
						buffer << "[WARNING] ";
						break;
					}

					case INFO:{
						buffer << "[INFO] ";
						break;
					}

					case DEBUG:{
						buffer << "[DEBUG] ";
						break;
					}

					default:{
						buffer << "[OTHER] ";
						break;
					}
				}
			}
		}
		template <typename T>
		Log & operator<<(T const & value)
		{
			if(currentLogLevel<=logMode){
				buffer << value;
			}
			return *this;
		}
		~Log(){
			if(currentLogLevel<=logMode){
				std::cout << buffer.str() << std::flush;
				std::filesystem::create_directory("logs");
				std::ofstream logFile;
				logFile.open ("logs/log.txt",std::ios::app);
				logFile << buffer.str();
				logFile.close();
			}
		}
		private:
		std::ostringstream buffer;
		LogLevel currentLogLevel;
	};
}

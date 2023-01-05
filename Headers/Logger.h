//=-= =-= =-= =-= =-= =-= =-= =-=       =-= =-= =-= JMJ =-= =-= =-=       =-= =-= =-= =-= =-= =-= =-= 
/*   What is this logger?
* This is used for cleanly outputting text to a log file(s) and/or the console, which can be helpful for debugging and similar.
* 
* To use this logger in your project, first #include it in a file you'd like to be able to use it in, and then write code to use it such as: 
* Logger::Log(Logger::INFO) << "The text you'd like to log goes here." << "\n";

*////=-= =-= =-= =-= =-= =-= =-= =-=       =-= =-= =-= =-= =-= =-= =-=       =-= =-= =-= =-= =-= =-= =-= 

#pragma once

#include <iostream>
#include <sstream>
#include <fstream>
#include <filesystem>


namespace Logger //(This namespace is used for organizational reasons.)
{
	// A list of the types of logs which can be made.)
	enum logTypes{ERROR, WARNING, INFO, TITLELESS, LOGGERFUNCTION, DEBUG}; //(Note that `DEBUG` is required to be last option due to certain checks in our code.)


	// This code block is used to determine whether you're compiling in debug mode or not, and affects lastmostUsableLogType accordingly.
	#ifndef NDEBUG
		const logTypes lastmostUsableLogType = DEBUG;
	#else
		const logTypes lastmostUsableLogType = LOGGERFUNCTION;
	#endif


	// The log class contains functions variables and functions used for making logging to a file actually happen.
	class Log
	{
		private:
			std::ostringstream buffer;
			logTypes currentlogType;
			static const unsigned short int loggerOutputtingMode = 3; // (Used to determine how you want log files to work. To see the different availible options, look at the code in the `~Log()` function.)
			static const bool shouldOutputToConsole = true;
			const std::string logFilesContainerDirectory = "logs";
			const std::string defaultSingularLogFileName = "log";
	
		public:
			Log (logTypes logTypes = INFO) // (An object constructor for Log objects, the default logging type is "INFO")
			{
				currentlogType = logTypes;

				// Part of ensuring that "DEBUG" logs only actually get logged when the program is compiled in debug mode (rather than in release mode.)
				if (!(currentlogType <= lastmostUsableLogType)) { return; }

				switch (currentlogType)
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
					
					case TITLELESS: { //(Intentioanlly adds nothing, one example of where you would use this would be if you just wanted to output a \n character.)
						break;
					}

					case LOGGERFUNCTION: { //(In the case that it's `LOGGERFUNCTION` we want to add nothing, as the inputted text isn't actually intended to be a log output but rather a command input.)
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

			
		// Defines what should happen when/if the `<<` operator is used to concatenate a string or character onto a created log object. (This is commonly used.)
		template <typename varType>
		Log & operator << (varType const & value)
		{
			if (currentlogType <= lastmostUsableLogType) { // (Helps ensure that DEBUG logs only get logged when the program is compiled in debug mode.)
				buffer << value;
			}
			return *this;
		}


		// The Log object deconstructor, contains the code where the text stored in the buffer variable is outputted to the log file(s) and optionally console.
		~Log()
		{
			// Part of ensuring that "DEBUG" logs only actually get logged when the program is compiled in debug mode (rather than in release mode.)
			if (!(currentlogType <= lastmostUsableLogType)) { return; }

			if (currentlogType == LOGGERFUNCTION) {
				if ((buffer.str() == "program_start") || (buffer.str() == "log_file_clear")) { //(Erases the contents of the main singular log file when the LOGGERFUNCTION command: "program_start" or "log_file_clear" is seen.)
					std::ofstream openedLogFile;
					openedLogFile.open(logFilesContainerDirectory + "/" + defaultSingularLogFileName + ".txt");
					std::filesystem::resize_file(logFilesContainerDirectory + "/" + defaultSingularLogFileName + ".txt", 0); //resizes the file to be 0 bytes, functionally erasing it's contents.
					openedLogFile.close();
				}
			}
			else {
				if (shouldOutputToConsole == true) {
					std::cout << buffer.str() << std::flush;
				}
				std::filesystem::create_directory(logFilesContainerDirectory);
				std::ofstream openedLogFile;
				openedLogFile.open(logFilesContainerDirectory + "/" + defaultSingularLogFileName + ".txt", std::ios::app);
				openedLogFile << buffer.str();
				openedLogFile.close();
			}
		}
	}; //end of class.
} //end of namespace.

//=-= =-= =-= =-= =-= =-= =-= =-=       =-= =-= =-= =-= =-= =-= =-=       =-= =-= =-= =-= =-= =-= =-= 
/*   A list of common LOGGERFUNCTION commands :
*
* "program_start" - Whether or not it's used in the ~Log function, always put this near the very start of Main(), before any other possible log text.
* "program_end" - Whether or not it's used in the ~Log function, always put this near the very end of Main(), after all other log text.
* "log_file_clear" - If it's being supported by the ~Log function, this will clear the contents of the currently opened log file.
*/

//=-= =-= =-= =-= =-= =-= =-= =-=       =-= =-= =-= =-= =-= =-= =-=       =-= =-= =-= =-= =-= =-= =-= 
// OPTIONAL	ALTERNATIVE ~LOG FUNCTION CODE:


// Outputs only optionally to the console.
/*if (currentlogType != LOGGERFUNCTION) {
	if (shouldOutputToConsole == true) {
		std::cout << buffer.str() << std::flush;
	}
}*/


// Outputs to a consistent singular not-automatically-cleared txt file, as well as optionally to the console.
/*if (currentlogType == LOGGERFUNCTION) {
	if (buffer.str() == "log_file_clear") { //(Erases the contents of the main singular log file when the LOGGERFUNCTION command: "log_file_clear" is seen.)
		std::ofstream openedLogFile;
		openedLogFile.open(logFilesContainerDirectory + "/" + defaultSingularLogFileName + ".txt");
		std::filesystem::resize_file(logFilesContainerDirectory + "/" + defaultSingularLogFileName + ".txt", 0); //resizes the file to be 0 bytes, functionally erasing it's contents.
		openedLogFile.close();
	}
}
else {
	if (shouldOutputToConsole == true) {
		std::cout << buffer.str() << std::flush;
	}
	std::filesystem::create_directory(logFilesContainerDirectory);
	std::ofstream openedLogFile;
	openedLogFile.open(logFilesContainerDirectory + "/" + defaultSingularLogFileName + ".txt", std::ios::app);
	openedLogFile << buffer.str();
	openedLogFile.close();
}*/


// Outputs to a consistent singular txt file which is automatically cleared each time the program starts or the "log_file_clear" function is called, as well as optionally to the console.
/*if (currentlogType == LOGGERFUNCTION) {
	if ((buffer.str() == "program_start") || (buffer.str() == "log_file_clear")) { //(Erases the contents of the main singular log file when the LOGGERFUNCTION command: "program_start" or "log_file_clear" is seen.)
		std::ofstream openedLogFile;
		openedLogFile.open(logFilesContainerDirectory + "/" + defaultSingularLogFileName + ".txt");
		std::filesystem::resize_file(logFilesContainerDirectory + "/" + defaultSingularLogFileName + ".txt", 0); //resizes the file to be 0 bytes, functionally erasing it's contents.
		openedLogFile.close();
	}
}
else {
	if (shouldOutputToConsole == true) {
		std::cout << buffer.str() << std::flush;
	}
	std::filesystem::create_directory(logFilesContainerDirectory);
	std::ofstream openedLogFile;
	openedLogFile.open(logFilesContainerDirectory + "/" + defaultSingularLogFileName + ".txt", std::ios::app);
	openedLogFile << buffer.str();
	openedLogFile.close();
}*/

//=-= =-= =-= =-= =-= =-= =-= =-=       =-= =-= =-= =-= =-= =-= =-=       =-= =-= =-= =-= =-= =-= =-= 
//=-= =-= =-= =-= =-= =-= =-= =-=       =-= =-= =-= =-= =-= =-= =-=       =-= =-= =-= =-= =-= =-= =-= 
/*   Logger.h file description:
* 
* Contains code used for outputting logging text to any appropriate log file(s) as well as also optionally the console.
* 
* To use the logger code in your project, first #include it in a file you'd like to use it in, and then write a line of code using it such as: 
* Logger::Log(Logger::INFO) << "The text you'd like to log goes here." << "\n";
* 
*////=-= =-= =-= =-= =-= =-= =-= =-=       =-= =-= =-= =-= =-= =-= =-=       =-= =-= =-= =-= =-= =-= =-= 

#pragma once

#include <iostream>
#include <sstream>
#include <fstream>
#include <filesystem>


namespace Logger //(The namespace "Logger" is used for organizational reasons.)
{
	// A list of the types of logs which can be made. (They can be referenced externally using code such as: "Logger::ERROR", etc.)
	enum logTypes{ERROR, WARNING, INFO, TITLELESS, LOGGERFUNCTION, DEBUG}; //(Note that `DEBUG` needs to be last option due to certain checks in our code.)


	// This code block is used to determine whether you're compiling in debug mode or not, and affects lastmostUsableLogType accordingly.
	#ifndef NDEBUG
		const logTypes lastmostUsableLogType = DEBUG;
	#else
		const logTypes lastmostUsableLogType = LOGGERFUNCTION;
	#endif


	// The log class contains functions used to do the actual logging.
	class Log
	{
		private:
			std::ostringstream buffer;
			logTypes currentlogType;
			static const unsigned short int loggerOutputtingMode = 3; // (Used to determine how you want log files to work. To see the different availible options, look at the code in the `~Log()` function.)
			static const bool shouldOutputToConsole = true;
			static const bool shouldNonUniqueLoggerFunctionCommandsBeProcessed = true;
			const std::string logFilesContainerDirectory = "logs";
			const std::string defaultSingularLogFileName = "log";
	
		public:
			Log (logTypes logTypes = INFO) // (An object constructor for Log objects, the default logging type is "INFO")
			{
				currentlogType = logTypes;

				// (Helps ensure that DEBUG logs only get logged when the program is compiled in debug mode.)
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

			// (A declaration for a function which processes common logfunctions which aren't unique to individual `loggerOutputtingMode` modes.)
			void inline process_nonunique_LOGGERFUNCTION_commands(std::string inputCommandName);
			
		// Defines what should happen when/if the `<<` operator is used to concatenate a string or character onto a created log object. (This is regularly done when logging text.)
		template <typename varType>
		Log & operator << (varType const & value)
		{
			if (currentlogType <= lastmostUsableLogType) { // (Helps ensure that DEBUG logs only get logged when the program is compiled in debug mode.)
				buffer << value;
			}
			return *this;
		}

		// The Log object deconstructor, contains the code where the text stored in the buffer variable is finally outputted to both the console and the appropriate log file.)
		~Log() //(Note that all of this code is ran everytime a Log object is deconstructed, such as for example when a Log object is created but then not stored anywhere.)
		{
			// (Helps ensure that DEBUG logs only get logged when the program is compiled in debug mode.)
			if (!(currentlogType <= lastmostUsableLogType)) { return; }

			switch (loggerOutputtingMode)
			{
				// Output mode: Do nothing. (NOTE: LOGGERFUNCTION commands are entirely disabled under this mode.)
				case 0: {
					break;
				}
				// Output mode: Only can output to the console, doesn't output to any log files.
				case 1: {
					if (currentlogType == LOGGERFUNCTION) {
						if (shouldNonUniqueLoggerFunctionCommandsBeProcessed == true) {
							process_nonunique_LOGGERFUNCTION_commands(buffer.str());
						}
					}
					else {
						if (shouldOutputToConsole == true) {
							std::cout << buffer.str() << std::flush;
						}
					}
					break;
				}
				// Output mode: Output to a consistent singular not-automatically-cleared txt file, and also optionally to the console.
				case 2: {
					if (currentlogType == LOGGERFUNCTION) {
						if (buffer.str() == "log_file_clear") { //(Erases the contents of the main singular log file when the LOGGERFUNCTION command: "log_file_clear" is seen.)
							std::ofstream openedLogFile;
							openedLogFile.open(logFilesContainerDirectory + "/" + defaultSingularLogFileName + ".txt");
							std::filesystem::resize_file(logFilesContainerDirectory + "/" + defaultSingularLogFileName + ".txt", 0); //resizes the file to be 0 bytes, functionally erasing it's contents.
							openedLogFile.close();
						}
						else if (shouldNonUniqueLoggerFunctionCommandsBeProcessed == true) {
							process_nonunique_LOGGERFUNCTION_commands(buffer.str());
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
					break;
				}
				// Output mode: Outputs to a consistent singular txt file which is automatically cleared each time the program starts or the "log_file_clear" function is called, and also optionally to the console.
				case 3: {
					if (currentlogType == LOGGERFUNCTION){
						if ((buffer.str() == "program_start")||(buffer.str() == "log_file_clear")) { //(Erases the contents of the main singular log file when the LOGGERFUNCTION command: "program_start" or "log_file_clear" is seen.)
							std::ofstream openedLogFile;
							openedLogFile.open(logFilesContainerDirectory + "/" + defaultSingularLogFileName + ".txt");
							std::filesystem::resize_file(logFilesContainerDirectory + "/" + defaultSingularLogFileName + ".txt", 0); //resizes the file to be 0 bytes, functionally erasing it's contents.
							openedLogFile.close();
						}
						else if (shouldNonUniqueLoggerFunctionCommandsBeProcessed == true) {
							process_nonunique_LOGGERFUNCTION_commands(buffer.str());
						}
					}
					else{
						if (shouldOutputToConsole == true) {
							std::cout << buffer.str() << std::flush;
						}
						std::filesystem::create_directory(logFilesContainerDirectory);
						std::ofstream openedLogFile;
						openedLogFile.open(logFilesContainerDirectory + "/" + defaultSingularLogFileName + ".txt", std::ios::app);
						openedLogFile << buffer.str();
						openedLogFile.close();
					}
					break;
				}
				// (The loggerOutputtingMode value should always be one of the available numbered options, so when it's not, we should alert the dev via the console that something went wrong.)
				default: {
					std::cout << "[WARNING: THE LOGGER HAS AN INVALID `loggerOutputtingMode` VALUE.]";
					break;
				} 
			}
		}
	};


	/*   List of standardized LOGGERFUNCTION commands:
	*
	* //// UNIQUE FUNCTIONS: [the specific code for the way that they work is dependant on the `loggerOutputtingMode`]
	* "program_start" - Call this when at/near the very start of a program you use the logger in, preferably before any other logging text.
	* "program_end" - Call this when at/near the very end of a program, such as when the window is closed if using OpenGL, preferably as the very last log output.
	* "log_file_clear" - Call this to clear the log file which is currently in use. It's a unique function because this would work differently based on `loggerOutputtingMode`.
	*
	*
	* //// NONUNIQUE FUNCTIONS: [the specific code for these functions are not dependant on ]
	* ...
	*/


	// (Currently just a placeholder.)
	inline void Log::process_nonunique_LOGGERFUNCTION_commands(std::string inputCommandName)
	{
		return;
	}
}


// ( Unrelatedly, here's some fun pastable comment-text art! )

// [Of Jcodefox]
//     /|/|      |\|\       /|/|      |\|\       |\|\      |\|\      /|/|        |\|\     |\_/|
//    (  ^^>    <^^  )     (  ''_>  <_''  )     (  ;;_>  <_;;   )    ( , '_>  <_' , )      o o 
//    /   |      |   \     /   | /  \ |   \     /  (|      |)  \    /  /|        |\  \    /_^_\

// [Of Pixer Pinecone]
//    \///¯>    <¯\\\/     \//0^0    0^0\\/     \//0^0    0^0\\/     \//0^0    0^0\\/    \/)^()\
//    /( 0^>    <^0 )\     /( o >    < o )\     /(^O >    < O^)\     /( . >    < . )\    /  v  )
//    _/  ¯_    _¯  \_     _/  ¯_    _¯  \_     _/  ^_    _^  \_     _/  ¯_    _¯  \_     _ ¯ _ 

//=-= =-= =-= =-= =-= =-= =-= =-=       =-= =-= =-= =-= =-= =-= =-=       =-= =-= =-= =-= =-= =-= =-= 
#pragma once

#include <string>
#include <vector>
#include <algorithm>

class Logger
{
    private:
        static const std::string filename;
        std::string loggerID;

        static std::vector<std::string> disabledLoggers;
    
    public:
        enum LogLevel
        {
            INFO = 1,
            WARNING = 2,
            ERROR = 3
        };
        enum ConsoleOutput
        {
            DISABLED = 0,
            ENABLED = 1
        };

        static LogLevel logLevel;
        static ConsoleOutput consoleOutput;

        Logger(std::string name);
        void log(std::string message, LogLevel loglvl = INFO);
        void log(char* message, LogLevel loglvl = INFO);

        static void disableLogger(std::string loggerID) {
            if(std::find(disabledLoggers.begin(), disabledLoggers.end(), loggerID) == disabledLoggers.end()){
                disabledLoggers.push_back(loggerID);
            }
        }
};
#pragma once

#include <string>

class Logger
{
    private:
        static const std::string filename;
        std::string loggerID;
    
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
};
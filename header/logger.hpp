#pragma once

#include <string>

class Logger
{
    private:
        static const std::string filename;
        static int loglevel;
        static bool consoleOutput;

        std::string loggerID;
    
    public:
        Logger(std::string name);
        void log(std::string message, int loglvl = 1);
        void log(char* message, int loglvl = 1);

        void setLogLevel(int loglvl);
        void setConsoleOutput(bool enableOutput);
};
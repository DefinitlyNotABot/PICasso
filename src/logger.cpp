#include "logger.hpp"
#include <iostream>
#include <algorithm>

const std::string Logger::filename = "PICasso.log";
Logger::LogLevel Logger::logLevel = Logger::INFO;
Logger::ConsoleOutput Logger::consoleOutput = Logger::ENABLED;
std::vector<std::string> Logger::disabledLoggers;

Logger::Logger(std::string name)
{
    loggerID = name;
}

void Logger::log(char* message, LogLevel loglvl)
{
    std::string s = message;
    log(s, loglvl);
}

void Logger::log(std::string message, LogLevel loglvl)
{
    if(loglvl < logLevel){
        return;
    }
    if(std::find(disabledLoggers.begin(), disabledLoggers.end(), loggerID) != disabledLoggers.end()){
        return;
    }

    std::string log = "[" + loggerID + "] -> " + message;

    if(consoleOutput){
        std::cout << log << std::endl;
    }
}
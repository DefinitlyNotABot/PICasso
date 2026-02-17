#include "logger.hpp"
#include <iostream>

const std::string Logger::filename = "PICasso.log";
Logger::LogLevel Logger::logLevel = Logger::INFO;
Logger::ConsoleOutput Logger::consoleOutput = Logger::ENABLED;


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

    std::string log = "[" + loggerID + "] -> " + message;

    if(consoleOutput){
        std::cout << log << std::endl;
    }
}
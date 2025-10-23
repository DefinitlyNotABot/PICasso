#include "../header/logger.hpp"
#include <iostream>

const std::string Logger::filename = "PICasso.log";
int Logger::loglevel = 1;
bool Logger::consoleOutput = true;


Logger::Logger(std::string name)
{
    loggerID = name;
}

void Logger::log(char* message, int loglvl)
{
    std::string s = message;
    log(s, loglvl);
}

void Logger::log(std::string message, int loglvl)
{
    if(loglvl < loglevel){
        return;
    }

    std::string log = "[" + loggerID + "] -> " + message;

    if(consoleOutput){
        std::cout << log << std::endl;
    }
}
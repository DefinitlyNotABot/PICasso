#include "instruction.hpp"
#include "program.hpp"
#include "pic.hpp"
#include "logger.hpp"

#include "alu.hpp"
#include <iostream>

int main()
{
    Logger::consoleOutput = Logger::ConsoleOutput::DISABLED;
    Logger::logLevel = Logger::LogLevel::INFO;

    PIC pic;
    pic.loadProgram("progs/TPicSim2.LST");

    std::cout << "Program loaded, starting execution..." << std::endl;

    pic.run();

    return 0;
}
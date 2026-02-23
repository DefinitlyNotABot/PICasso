#include "instruction.hpp"
#include "program.hpp"
#include "pic.hpp"
#include "logger.hpp"

#include "alu.hpp"
#include <iostream>

int main()
{
    Logger::disableLogger("Compiler");
    PIC pic;
    pic.loadProgram("progs/TPicSim6.LST");

    std::cout << "Program loaded, starting execution..." << std::endl;

    pic.run();

    return 0;
}
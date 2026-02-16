#include "instruction.hpp"
#include "program.hpp"
#include "pic.hpp"

#include "alu.hpp"
#include <iostream>

int main()
{

    PIC pic;
    pic.loadProgram("progs/TPicSim1.LST");

    std::cout << "Program loaded, starting execution..." << std::endl;

    pic.run();

    return 0;
}
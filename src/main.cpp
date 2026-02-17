#include "instruction.hpp"
#include "program.hpp"
#include "pic.hpp"

#include "alu.hpp"
#include <iostream>
#include <thread>

void picRuntimeThread(PIC& pic) {
    pic.run();
}

int main()
{

    PIC pic;
    pic.loadProgram("progs/TPicSim1.LST");

    std::cout << "Program loaded, starting execution..." << std::endl;

    std::thread t(picRuntimeThread, std::ref(pic));
    t.join();

    return 0;
}
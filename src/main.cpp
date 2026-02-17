#include "instruction.hpp"
#include "program.hpp"
#include "pic.hpp"
#include "TerminalGUI.hpp"

#include "alu.hpp"
#include <iostream>
#include <thread>

void picRuntimeThread(PIC &pic)
{
    pic.run();
}

void guiRuntimeThread(TerminalGUI &gui)
{
    gui.loop();
}

int main()
{
    TerminalGUI gui;

    std::thread guiThread(guiRuntimeThread, std::ref(gui));

    PIC pic;
    pic.loadProgram("progs/TPicSim1.LST");

    std::cout << "Program loaded, starting execution..." << std::endl;

    std::thread picThread(picRuntimeThread, std::ref(pic));

    picThread.join();
    guiThread.join();

    return 0;
}
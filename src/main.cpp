#include "instruction.hpp"
#include "program.hpp"

#include "alu.hpp"
#include <iostream>

int main()
{
    Program p;

    std::string prog = "progs/TPicSim1.LST";

    p.loadProgram(prog);

    ALU alu;

    for(uint16_t i = 0; i < p.getProgramLength(); i++){
        Instruction& inst = p.getInstructionAt(i);
        std::cout << inst.getName() << " -> ";
        alu.executeInstruction(inst);
        
    }

    return 0;
}
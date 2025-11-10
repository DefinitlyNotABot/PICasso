#include "program.hpp"

#include "alu.hpp"

int main()
{
    Program p;

    std::string prog = "progs/TPicSim1.LST";

    p.loadProgram(prog);

    ALU alu;

    for(uint16_t i = 0; i < p.getProgramLength(); i++){
        alu.executeInstruction(p.getInstructionAt(i));
    }

    return 0;
}
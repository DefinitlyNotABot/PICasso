#include "pic.hpp"

PIC::PIC() : alu(), loadedProgram(), ram()
{
    Instruction::ram = std::shared_ptr<Ram>(&ram, [](Ram*) {});
    Instruction::W = std::shared_ptr<Register>(&W, [](Register*) {});
}

PIC::~PIC()
{
}

void PIC::loadProgram(const std::string& program)
{
    loadedProgram.loadProgram(program);
}

void PIC::run()
{
    // loop through all instructions in loadedProgram and execute them using alu
    for (uint16_t i = 0; i < loadedProgram.getProgramLength(); i++)
    {
        Instruction& inst = loadedProgram.getInstructionAt(i);
        alu.executeInstruction(inst);
    }
}
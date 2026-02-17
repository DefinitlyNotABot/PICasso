#include "pic.hpp"
#include <iostream>

PIC::PIC() : alu(), loadedProgram(), memoryInterface()
{
    Instruction::memoryInterface = std::shared_ptr<MemoryInterface>(&memoryInterface, [](MemoryInterface*) {});
    Instruction::W = std::shared_ptr<Register>(&W, [](Register*) {});
}

PIC::~PIC()
{
}

void PIC::loadProgram(const std::string& program)
{
    loadedProgram.loadProgram(program);
}

void PIC::reset(){
    memoryInterface.reset();
    W.writeByte(0);
}

void PIC::run()
{
    for(int i = 0; i < 10; i++){
        step();
    }
}

void PIC::step(){
    if (loadedProgram.getProgramLength() == 0)
    {
        throw std::runtime_error("No program loaded");
    }

    uint8_t programCounter = memoryInterface.getProgramCounter();
    memoryInterface.incrementProgramCounterLow();

    Instruction& currentInstruction = loadedProgram.getInstructionAt(programCounter);
    alu.executeInstruction(currentInstruction);

    std::cout << "PCL: " << static_cast<int>(programCounter) << " Executed instruction: " << currentInstruction.getName() << std::endl;
    
}
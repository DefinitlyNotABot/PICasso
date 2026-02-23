#include "pic.hpp"
#include <iomanip>
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
    for(int i = 0; i < 20; i++){
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

    printStep(currentInstruction);
}

void PIC::printState(){
    std::cout << "PCL: " << static_cast<int>(memoryInterface.getProgramCounter()) << std::endl;
    std::cout << "W: 0x" << std::hex << std::uppercase << std::setw(2) << std::setfill('0')
              << static_cast<int>(W.readByte()) << std::dec << std::nouppercase << std::setfill(' ') << std::endl;
    std::cout << "STATUS: " << static_cast<int>(memoryInterface.readRegister(MemoryInterface::STATUS)) << std::endl;
}

void PIC::printStep(Instruction& instruction){
    
    std::cout << "PCL: " << static_cast<int>(memoryInterface.getProgramCounter()) << " ";
    std::cout << "Command: " << std::left << std::setw(10) << instruction.getName() << std::right << " ";
    std::cout << "W: 0x" << std::hex << std::uppercase << std::setw(2) << std::setfill('0')
              << static_cast<int>(W.readByte()) << std::dec << std::nouppercase << std::setfill(' ') << " ";
    std::cout << " C: " << memoryInterface.readStatusBit(MemoryInterface::C) << " ";
    std::cout << "DC: " << memoryInterface.readStatusBit(MemoryInterface::DC) << " ";
    std::cout << "Z: " << memoryInterface.readStatusBit(MemoryInterface::Z) << std::endl;
}
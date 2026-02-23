#include "pic.hpp"
#include <iomanip>
#include <iostream>

PIC::PIC() : alu(), loadedProgram(), memoryInterface(), logger("PIC")
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


    // build string like this:
    /*
        std::cout << "PCL: " << static_cast<int>(memoryInterface.getProgramCounter()) << " ";
    std::cout << "Command: " << std::left << std::setw(10) << instruction.getName() << std::right << " ";
    std::cout << "W: 0x" << std::hex << std::uppercase << std::setw(2) << std::setfill('0')
              << static_cast<int>(W.readByte()) << std::dec << std::nouppercase << std::setfill(' ') << " ";
    std::cout << " C: " << memoryInterface.readStatusBit(MemoryInterface::C) << " ";
    std::cout << "DC: " << memoryInterface.readStatusBit(MemoryInterface::DC) << " ";
    std::cout << "Z: " << memoryInterface.readStatusBit(MemoryInterface::Z) << std::endl;
    */

    // add ram:0Ch and ram:0Dh
    std::stringstream ss;
    ss << "PCL: " << static_cast<int>(memoryInterface.getProgramCounter()) << " Command: " << std::left << std::setw(10) << instruction.getName() << std::right << " W: 0x" << std::hex << std::uppercase << std::setw(2) << std::setfill('0')
       << static_cast<int>(W.readByte()) << std::dec << std::nouppercase << std::setfill(' ') << " C: " << memoryInterface.readStatusBit(MemoryInterface::C) << " DC: " << memoryInterface.readStatusBit(MemoryInterface::DC) << " Z: " << memoryInterface.readStatusBit(MemoryInterface::Z) << " RAM:0Ch: 0x" << std::hex << std::uppercase << std::setw(2) << std::setfill('0') << static_cast<int>(memoryInterface.readRegister(0x0C)) << " RAM:0Dh: 0x" << std::hex << std::uppercase << std::setw(2) << std::setfill('0') << static_cast<int>(memoryInterface.readRegister(0x0D));
    logger.log(ss.str());
}

uint8_t PIC::getProgramCounter(){
    return memoryInterface.getProgramCounter();
}

uint8_t PIC::getStatusBit(char c){
    if(c == 'W'){
        return W.readByte();
    }else if(c == 'C'){
        return memoryInterface.readStatusBit(MemoryInterface::C);
    } else if(c == 'D'){
        return memoryInterface.readStatusBit(MemoryInterface::DC);
    } else if(c == 'Z'){
        return memoryInterface.readStatusBit(MemoryInterface::Z);
    } else {
        throw std::invalid_argument("Invalid status bit: " + std::string(1, c));
    }
}
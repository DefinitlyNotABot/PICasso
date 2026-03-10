#include "pic.hpp"
#include <iomanip>
#include <iostream>
#include <stdexcept>
#include "jump.hpp"

PIC::PIC() : alu(), loadedProgram(), logger("PIC")
{
    memoryInterface = std::make_shared<MemoryInterface>();
    prescaler = std::make_shared<Prescaler>(memoryInterface);
    
    timer = Timer(prescaler, memoryInterface);
    Instruction::memoryInterface = memoryInterface;
    Instruction::W = std::shared_ptr<Register>(&W, [](Register*) {});

    Jump::timer = std::make_shared<Timer>(timer);
}

PIC::~PIC()
{
}

void PIC::loadProgram(const std::string& program)
{
    std::lock_guard<std::mutex> lock(executionMutex);
    loadedProgram.loadProgram(program);
}

void PIC::reset(){
    std::lock_guard<std::mutex> lock(executionMutex);
    memoryInterface->reset();
    W.writeByte(0);
}



void PIC::printState(){
    std::cout << "PCL: " << static_cast<int>(memoryInterface->getProgramCounter()) << std::endl;
    std::cout << "W: 0x" << std::hex << std::uppercase << std::setw(2) << std::setfill('0')
              << static_cast<int>(W.readByte()) << std::dec << std::nouppercase << std::setfill(' ') << std::endl;
    std::cout << "STATUS: " << static_cast<int>(memoryInterface->readRegister(MemoryInterface::STATUS)) << std::endl;
}

void PIC::printStep(Instruction& instruction){


    // build string like this:
    /*
        std::cout << "PCL: " << static_cast<int>(memoryInterface->getProgramCounter()) << " ";
    std::cout << "Command: " << std::left << std::setw(10) << instruction.getName() << std::right << " ";
    std::cout << "W: 0x" << std::hex << std::uppercase << std::setw(2) << std::setfill('0')
              << static_cast<int>(W.readByte()) << std::dec << std::nouppercase << std::setfill(' ') << " ";
    std::cout << " C: " << memoryInterface->readStatusBit(MemoryInterface::C) << " ";
    std::cout << "DC: " << memoryInterface->readStatusBit(MemoryInterface::DC) << " ";
    std::cout << "Z: " << memoryInterface->readStatusBit(MemoryInterface::Z) << std::endl;
    */

    // add ram:0Ch and ram:0Dh
    std::stringstream ss;
    ss << "PCL: " << static_cast<int>(memoryInterface->getProgramCounter()) << " Command: " << std::left << std::setw(10) << instruction.getName() << std::right << " W: 0x" << std::hex << std::uppercase << std::setw(2) << std::setfill('0')
       << static_cast<int>(W.readByte()) << std::dec << std::nouppercase << std::setfill(' ') << " C: " << memoryInterface->readStatusBit(MemoryInterface::C) << " DC: " << memoryInterface->readStatusBit(MemoryInterface::DC) << " Z: " << memoryInterface->readStatusBit(MemoryInterface::Z) << " RAM:0Ch: 0x" << std::hex << std::uppercase << std::setw(2) << std::setfill('0') << static_cast<int>(memoryInterface->readRegister(0x0C)) << " RAM:1Fh: 0x" << std::hex << std::uppercase << std::setw(2) << std::setfill('0') << static_cast<int>(memoryInterface->readRegister(0x1F));
    logger.log(ss.str());
}

uint8_t PIC::getProgramCounter(){
    std::lock_guard<std::mutex> lock(executionMutex);
    return memoryInterface->getProgramCounter();
}

uint8_t PIC::getStatusBit(char c){
    std::lock_guard<std::mutex> lock(executionMutex);
    if(c == 'W'){
        return W.readByte();
    }else if(c == 'C'){
        return memoryInterface->readStatusBit(MemoryInterface::C);
    } else if(c == 'D'){
        return memoryInterface->readStatusBit(MemoryInterface::DC);
    } else if(c == 'Z'){
        return memoryInterface->readStatusBit(MemoryInterface::Z);
    } else {
        throw std::invalid_argument("Invalid status bit: " + std::string(1, c));
    }
}

void PIC::getSnapshot(PICSnapshot& snapshot)
{
    std::lock_guard<std::mutex> lock(executionMutex);

    snapshot.w = W.readByte();
    snapshot.programCounter = memoryInterface->getProgramCounter();
    snapshot.programLength = loadedProgram.getProgramLength();

    if (snapshot.programLength > 0 && snapshot.programCounter < snapshot.programLength)
    {
        snapshot.currentInstructionName = loadedProgram.getInstructionAt(snapshot.programCounter).getName();
    }

    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 0x50; j++)
        {
            try{
                snapshot.memory[i][j] = memoryInterface->readRegister(static_cast<uint8_t>(j), i);
                snapshot.validMemory[i][j] = true;
            } catch (const std::exception&){
                snapshot.memory[i][j] = 0;
                snapshot.validMemory[i][j] = false;
            }
        }
    }
}

bool PIC::tryStep(std::string* errorMessage)
{
    std::lock_guard<std::mutex> lock(executionMutex);
    if (loadedProgram.getProgramLength() == 0)
    {
        if (errorMessage)
        {
            *errorMessage = "No program loaded";
        }
        return false;
    }

    try
    {
        uint8_t programCounter = memoryInterface->getProgramCounter();
        memoryInterface->incrementProgramCounterLow();
        Instruction& currentInstruction = loadedProgram.getInstructionAt(programCounter);

        uint16_t executionTime = alu.executeInstruction(currentInstruction);
        for(int i = 0; i < executionTime; i++){
            timer.timeStep();
            totalSimulatedTimeUs++;
        }

        // printStep(currentInstruction);
        return true;
    }
    catch (const std::exception& ex)
    {
        if (errorMessage)
        {
            *errorMessage = ex.what();
        }
        return false;
    }
}

bool PIC::tryWriteRegister(uint8_t address, uint8_t value, std::string* errorMessage)
{
    std::lock_guard<std::mutex> lock(executionMutex);
    try
    {
        memoryInterface->writeRegister(address, value);
        return true;
    }
    catch (const std::exception& ex)
    {
        if (errorMessage)
        {
            *errorMessage = ex.what();
        }
        return false;
    }
}

bool PIC::tryWriteRegister(uint8_t address, uint8_t value, bool bank, std::string* errorMessage)
{
    std::lock_guard<std::mutex> lock(executionMutex);
    try
    {
        memoryInterface->writeRegister(address, value, bank);
        return true;
    }
    catch (const std::exception& ex)
    {
        if (errorMessage)
        {
            *errorMessage = ex.what();
        }
        return false;
    }
}

bool PIC::tryToggleBit(uint8_t address, uint8_t bit, std::string* errorMessage)
{
    std::lock_guard<std::mutex> lock(executionMutex);
    try
    {
        bool currentValue = memoryInterface->readBit(address, bit);
        memoryInterface->writeBit(address, bit, !currentValue);
        return true;
    }
    catch (const std::exception& ex)
    {
        if (errorMessage)
        {
            *errorMessage = ex.what();
        }
        return false;
    }
}

bool PIC::tryToggleBit(uint8_t address, uint8_t bit, bool bank, std::string* errorMessage)
{
    std::lock_guard<std::mutex> lock(executionMutex);
    try
    {
        uint8_t currentValue = memoryInterface->readRegister(address, bank);
        uint8_t mask = static_cast<uint8_t>(1U << bit);
        uint8_t updatedValue = static_cast<uint8_t>(currentValue ^ mask);
        memoryInterface->writeRegister(address, updatedValue, bank);
        return true;
    }
    catch (const std::exception& ex)
    {
        if (errorMessage)
        {
            *errorMessage = ex.what();
        }
        return false;
    }
}

bool PIC::tryGetInstructionName(uint16_t index, std::string& instructionName, std::string* errorMessage)
{
    std::lock_guard<std::mutex> lock(executionMutex);
    if (index >= loadedProgram.getProgramLength())
    {
        if (errorMessage)
        {
            *errorMessage = "Instruction index out of range";
        }
        return false;
    }

    try
    {
        instructionName = loadedProgram.getInstructionAt(index).getName();
        return true;
    }
    catch (const std::exception& ex)
    {
        if (errorMessage)
        {
            *errorMessage = ex.what();
        }
        return false;
    }
}


uint64_t PIC::getSimulatedTimeUs()
{
    std::lock_guard<std::mutex> lock(executionMutex);
    return totalSimulatedTimeUs;
}
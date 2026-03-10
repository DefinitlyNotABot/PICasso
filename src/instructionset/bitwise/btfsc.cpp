#include "btfsc.hpp"

BTFSC::BTFSC(uint16_t instruction) {
    bit = (instruction & 0b1110000000) >> 7;
    file = instruction & 0b0001111111;
}

uint16_t BTFSC::execute()
{
    if(!memoryInterface->readBit(loadAddress(file), bit)){
        memoryInterface->incrementProgramCounterLow();
        return 2; // execution time in cycles (1 for btfsc + 1 for skipping the next instruction)
    }
    return 1; // execution time in cycles
}

std::string BTFSC::getName()
{
    return "btfsc";
}


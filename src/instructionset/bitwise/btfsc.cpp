#include "btfsc.hpp"

BTFSC::BTFSC(uint16_t instruction) {
    bit = (instruction & 0b1110000000) >> 7;
    file = instruction & 0b0001111111;
}

uint16_t BTFSC::execute()
{
    if(!memoryInterface->readBit(file, bit)){
        memoryInterface->incrementProgramCounterLow();
    }
    return 0;
}

std::string BTFSC::getName()
{
    return "btfsc";
}


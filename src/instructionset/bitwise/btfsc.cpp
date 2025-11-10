#include "btfsc.hpp"

BTFSC::BTFSC(uint16_t instruction) {
    bit = (instruction & 0b1110000000) >> 7;
    file = instruction & 0b0001111111;
}

uint16_t BTFSC::execute()
{
return 0;
}
// Implementation of the instruction name getter
std::string BTFSC::getName()
{
    return "btfsc";
}


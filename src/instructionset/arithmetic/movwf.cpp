#include "movwf.hpp"

MOVWF::MOVWF(uint16_t instruction) {
    file = instruction & 0b01111111;
}

uint16_t MOVWF::execute()
{
return 0;
}
// Implementation of the instruction name getter
std::string MOVWF::getName()
{
    return "movwf";
}


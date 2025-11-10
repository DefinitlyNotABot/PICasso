#include "comf.hpp"

COMF::COMF(uint16_t instruction) {
    destination = instruction & 0b10000000;
    file = instruction & 0b01111111;
}

uint16_t COMF::execute()
{
return 0;
}
// Implementation of the instruction name getter
std::string COMF::getName()
{
    return "comf";
}


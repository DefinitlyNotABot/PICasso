#include "incf.hpp"

INCF::INCF(uint16_t instruction) {
    destination = instruction & 0b10000000;
    file = instruction & 0b01111111;
}

uint16_t INCF::execute()
{
return 0;
}
// Implementation of the instruction name getter
std::string INCF::getName()
{
    return "incf";
}


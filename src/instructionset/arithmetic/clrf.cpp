#include "clrf.hpp"

CLRF::CLRF(uint16_t instruction) {
    file = instruction & 0b01111111;
}

uint16_t CLRF::execute()
{
return 0;
}
// Implementation of the instruction name getter
std::string CLRF::getName()
{
    return "clrf";
}


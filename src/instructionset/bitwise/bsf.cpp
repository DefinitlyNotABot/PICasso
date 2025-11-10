#include "bsf.hpp"

BSF::BSF(uint16_t instruction) {
    bit = (instruction & 0b1110000000) >> 7;
    file = instruction & 0b0001111111;
}

uint16_t BSF::execute()
{
return 0;
}
// Implementation of the instruction name getter
std::string BSF::getName()
{
    return "bsf";
}


#include "swapf.hpp"

SWAPF::SWAPF(uint16_t instruction) {
    destination = instruction & 0b10000000;
    file = instruction & 0b01111111;
}

uint16_t SWAPF::execute()
{
    return 0;
}

std::string SWAPF::getName()
{
    return "swapf";
}


#include "iorwf.hpp"

IORWF::IORWF(uint16_t instruction) {
    destination = instruction & 0b10000000;
    file = instruction & 0b01111111;
}

uint16_t IORWF::execute()
{
    return 0;
}

std::string IORWF::getName()
{
    return "iorwf";
}


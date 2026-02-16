#include "subwf.hpp"

SUBWF::SUBWF(uint16_t instruction) {
    destination = instruction & 0b10000000;
    file = instruction & 0b01111111;
}

uint16_t SUBWF::execute()
{
    return 0;
}

std::string SUBWF::getName()
{
    return "subwf";
}


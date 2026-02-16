#include "movf.hpp"

MOVF::MOVF(uint16_t instruction) {
    destination = instruction & 0b10000000;
    file = instruction & 0b01111111;
}

uint16_t MOVF::execute()
{
    return 0;
}

std::string MOVF::getName()
{
    return "movf";
}


#include "movlw.hpp"

MOVLW::MOVLW(uint16_t instruction) {
    literal = instruction & 0xFF;
}

uint16_t MOVLW::execute()
{
    return 0;
}

std::string MOVLW::getName()
{
    return "movlw";
}


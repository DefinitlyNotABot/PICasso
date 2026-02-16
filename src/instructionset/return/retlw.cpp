#include "retlw.hpp"

RETLW::RETLW(uint16_t instruction) {
    literal = instruction & 0xFF;
}

uint16_t RETLW::execute()
{
    return 0;
}

std::string RETLW::getName()
{
    return "retlw";
}


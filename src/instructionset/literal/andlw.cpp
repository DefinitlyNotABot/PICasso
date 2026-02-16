#include "andlw.hpp"

ANDLW::ANDLW(uint16_t instruction) {
    literal = instruction & 0xFF;
}

uint16_t ANDLW::execute()
{
    return 0;
}

std::string ANDLW::getName()
{
    return "andlw";
}


#include "xorlw.hpp"

XORLW::XORLW(uint16_t instruction) {
    literal = instruction & 0xFF;
}

uint16_t XORLW::execute()
{
    return 0;
}

std::string XORLW::getName()
{
    return "xorlw";
}


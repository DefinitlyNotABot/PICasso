#include "xorlw.hpp"

XORLW::XORLW(uint16_t instruction) {
    literal = instruction & 0xFF;
}

uint16_t XORLW::execute()
{
    uint16_t result = literal ^ W->readByte();
    W->writeByte(result);
    SET_ZERO_FLAG_W
    return 0;
}

std::string XORLW::getName()
{
    return "xorlw";
}


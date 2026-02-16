#include "andlw.hpp"

ANDLW::ANDLW(uint16_t instruction) {
    literal = instruction & 0xFF;
}

uint16_t ANDLW::execute()
{
    uint16_t result = literal & W->readByte();
    W->writeByte(result);
    SET_ZERO_FLAG_W
    return 0;
}

std::string ANDLW::getName()
{
    return "andlw";
}


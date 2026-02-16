#include "iorlw.hpp"

IORLW::IORLW(uint16_t instruction) {
    literal = instruction & 0xFF;
}

uint16_t IORLW::execute()
{
    uint16_t result = literal | W->readByte();
    W->writeByte(result);
    SET_ZERO_FLAG_W
    return 0;
}

std::string IORLW::getName()
{
    return "iorlw";
}


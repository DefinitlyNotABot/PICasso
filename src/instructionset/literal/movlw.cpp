#include "movlw.hpp"

MOVLW::MOVLW(uint16_t instruction) {
    literal = instruction & 0xFF;
}

uint16_t MOVLW::execute()
{
    W->writeByte(literal);
    return 0;
}

std::string MOVLW::getName()
{
    return "movlw";
}


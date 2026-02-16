#include "btfss.hpp"

BTFSS::BTFSS(uint16_t instruction) {
    bit = (instruction & 0b1110000000) >> 7;
    file = instruction & 0b0001111111;
}

uint16_t BTFSS::execute()
{
    return 0;
}

std::string BTFSS::getName()
{
    return "btfss";
}


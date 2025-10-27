#include "../../header/instructionset/btfss.hpp"

BTFSS::BTFSS(uint16_t instruction) {
    bit = (instruction & 0b1110000000) >> 7;
    file = instruction & 0b0001111111;
}

void BTFSS::execute()
{
}

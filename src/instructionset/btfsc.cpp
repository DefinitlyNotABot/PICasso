#include "../../header/instructionset/btfsc.hpp"

BTFSC::BTFSC(uint16_t instruction) {
    bit = (instruction & 0b1110000000) >> 7;
    file = instruction & 0b0001111111;
}

void BTFSC::execute()
{
}

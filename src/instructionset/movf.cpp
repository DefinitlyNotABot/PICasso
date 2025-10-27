#include "../../header/instructionset/movf.hpp"

MOVF::MOVF(uint16_t instruction) {
    destination = instruction & 0b10000000;
    file = instruction & 0b01111111;
}

void MOVF::execute()
{
}

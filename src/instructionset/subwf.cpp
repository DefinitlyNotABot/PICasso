#include "../../header/instructionset/subwf.hpp"

SUBWF::SUBWF(uint16_t instruction) {
    destination = instruction & 0b10000000;
    file = instruction & 0b01111111;
}

void SUBWF::execute()
{
}

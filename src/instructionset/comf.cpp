#include "../../header/instructionset/comf.hpp"

COMF::COMF(uint16_t instruction) {
    destination = instruction & 0b10000000;
    file = instruction & 0b01111111;
}

void COMF::execute()
{
}

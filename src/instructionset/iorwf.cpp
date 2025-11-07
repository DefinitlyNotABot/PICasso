#include "../../header/instructionset/iorwf.hpp"

IORWF::IORWF(uint16_t instruction) {
    destination = instruction & 0b10000000;
    file = instruction & 0b01111111;
}

void IORWF::execute()
{
}

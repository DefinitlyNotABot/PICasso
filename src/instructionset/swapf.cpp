#include "../../header/instructionset/swapf.hpp"

SWAPF::SWAPF(uint16_t instruction) {
    destination = instruction & 0b10000000;
    file = instruction & 0b01111111;
}

void SWAPF::execute()
{
}

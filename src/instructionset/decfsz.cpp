#include "../../header/instructionset/decfsz.hpp"

DECFSZ::DECFSZ(uint16_t instruction) {
    destination = instruction & 0b10000000;
    file = instruction & 0b01111111;
}

void DECFSZ::execute()
{
}

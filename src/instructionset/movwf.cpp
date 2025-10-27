#include "../../header/instructionset/movwf.hpp"

MOVWF::MOVWF(uint16_t instruction) {
    file = instruction & 0b01111111;
}

void MOVWF::execute()
{
}

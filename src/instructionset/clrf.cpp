#include "../../header/instructionset/clrf.hpp"

CLRF::CLRF(uint16_t instruction) {
    file = instruction & 0b01111111;
}

void CLRF::execute()
{
}

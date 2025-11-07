#include "../../header/instructionset/retlw.hpp"

RETLW::RETLW(uint16_t instruction) {
    file = instruction & 0xFF;
}

void RETLW::execute()
{
}

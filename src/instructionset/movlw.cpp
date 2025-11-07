#include "../../header/instructionset/movlw.hpp"

MOVLW::MOVLW(uint16_t instruction) {
    file = instruction & 0xFF;
}

void MOVLW::execute()
{
}

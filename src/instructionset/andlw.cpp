#include "../../header/instructionset/andlw.hpp"

ANDLW::ANDLW(uint16_t instruction) {
    literal = instruction & 0xFF;
}

void ANDLW::execute()
{
}

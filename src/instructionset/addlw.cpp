#include "../../header/instructionset/addlw.hpp"

ADDLW::ADDLW(uint16_t instruction) {
    literal = instruction & 0xFF;
}

void ADDLW::execute()
{
}

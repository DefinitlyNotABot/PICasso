#include "../../header/instructionset/xorlw.hpp"

XORLW::XORLW(uint16_t instruction) {
    literal = instruction & 0xFF;
}

void XORLW::execute()
{
}

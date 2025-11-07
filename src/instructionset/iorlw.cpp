#include "../../header/instructionset/iorlw.hpp"

IORLW::IORLW(uint16_t instruction) {
    literal = instruction & 0xFF;
}

void IORLW::execute()
{
}

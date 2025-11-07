#include "../../header/instructionset/goto.hpp"

GOTO::GOTO(uint16_t instruction) {
    address = instruction & 0x7FF;
}

void GOTO::execute()
{
}

#include "../../header/instructionset/call.hpp"

CALL::CALL(uint16_t instruction) {
    address = instruction & 0x7FF;
}

void CALL::execute()
{
}

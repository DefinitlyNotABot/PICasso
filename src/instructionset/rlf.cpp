#include "../../header/instructionset/rlf.hpp"

RLF::RLF(uint16_t instruction) {
    destination = instruction & 0b10000000;
    file = instruction & 0b01111111;
}

void RLF::execute()
{
}

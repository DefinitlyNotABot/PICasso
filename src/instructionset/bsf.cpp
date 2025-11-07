#include "../../header/instructionset/bsf.hpp"

BSF::BSF(uint16_t instruction) {
    bit = (instruction & 0b1110000000) >> 7;
    file = instruction & 0b0001111111;
}

void BSF::execute()
{
}

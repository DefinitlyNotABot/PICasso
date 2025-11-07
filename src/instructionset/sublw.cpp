#include "../../header/instructionset/sublw.hpp"

SUBLW::SUBLW(uint16_t instruction) {
    literal = instruction & 0xFF;
}

void SUBLW::execute()
{
}

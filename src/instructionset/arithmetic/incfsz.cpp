#include "incfsz.hpp"

INCFSZ::INCFSZ(uint16_t instruction) {
    destination = instruction & 0b10000000;
    file = instruction & 0b01111111;
}

uint16_t INCFSZ::execute()
{
return 0;
}

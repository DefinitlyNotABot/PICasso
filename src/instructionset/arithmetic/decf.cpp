#include "decf.hpp"

DECF::DECF(uint16_t instruction) {
    destination = instruction & 0b10000000;
    file = instruction & 0b01111111;
}

uint16_t DECF::execute()
{
return 0;
}

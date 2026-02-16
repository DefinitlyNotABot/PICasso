#include "rrf.hpp"

RRF::RRF(uint16_t instruction) {
    destination = instruction & 0b10000000;
    file = instruction & 0b01111111;
}

uint16_t RRF::execute()
{
    return 0;
}

std::string RRF::getName()
{
    return "rrf";
}


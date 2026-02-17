#include "bcf.hpp"

BCF::BCF(uint16_t instruction) {
    bit = (instruction & 0b1110000000) >> 7;
    file = instruction & 0b0001111111;
}

uint16_t BCF::execute()
{
    memoryInterface->writeBit(file, bit, false);
    return 0;
}

std::string BCF::getName()
{
    return "bcf";
}


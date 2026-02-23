#include "bsf.hpp"

BSF::BSF(uint16_t instruction) {
    bit = (instruction & 0b1110000000) >> 7;
    file = instruction & 0b0001111111;
}

uint16_t BSF::execute()
{
    memoryInterface->writeBit(loadAddress(file), bit, true);
    return 0;
}

std::string BSF::getName()
{
    return "bsf";
}


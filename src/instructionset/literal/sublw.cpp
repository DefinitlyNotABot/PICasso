#include "sublw.hpp"

SUBLW::SUBLW(uint16_t instruction) {
    literal = instruction & 0xFF;
}

uint16_t SUBLW::execute()
{
    uint16_t result = (literal - W->readByte()) & 0xFF;
    W->writeByte(result);
    memoryInterface->writeStatusBit(MemoryInterface::StatusBits::C, literal >= W->readByte());
    memoryInterface->writeStatusBit(MemoryInterface::StatusBits::DC, ((literal & 0x0F) - (W->readByte() & 0x0F)) >= 0);
    SET_ZERO_FLAG_W
    return 0;
}

std::string SUBLW::getName()
{
    return "sublw";
}


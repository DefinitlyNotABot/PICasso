#include "addlw.hpp"

ADDLW::ADDLW(uint16_t instruction) {
    literal = instruction & 0xFF;
}

uint16_t ADDLW::execute()
{
    uint16_t result = (literal + W->readByte()) & 0xFF;
    memoryInterface->writeStatusBit(MemoryInterface::StatusBits::DC, ((literal & 0x0F) + (W->readByte() & 0x0F)) > 0x0F);
    W->writeByte(result);
    memoryInterface->writeStatusBit(MemoryInterface::StatusBits::C, result > 0xFF);
    SET_ZERO_FLAG_W
    return 0;
}

std::string ADDLW::getName()
{
    return "addlw";
}


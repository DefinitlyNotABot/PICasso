#include "addlw.hpp"

ADDLW::ADDLW(uint16_t instruction) {
    literal = instruction & 0xFF;
}

uint16_t ADDLW::execute()
{
    uint16_t result = (literal + W->readByte()) & 0xFF;
    W->writeByte(result);
    ram->writeStatusBit(Ram::C, result > 0xFF);
    ram->writeStatusBit(Ram::DC, ((literal & 0x0F) + (W->readByte() & 0x0F)) > 0x0F);
    SET_ZERO_FLAG_W
    return 0;
}

std::string ADDLW::getName()
{
    return "addlw";
}


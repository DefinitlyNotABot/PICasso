#include "../../header/memory/register.hpp"
#include <stdexcept>

Register::Register()
{
}

void Register::writeByte(uint8_t value)
{
    byte.setByte(value);
}

void Register::writeHighNibble(uint8_t value)
{
    byte.setHighNibble(value);
}

void Register::writeLowNibble(uint8_t value)
{
    byte.setLowNibble(value);
}

void Register::writeBit(uint8_t bit, bool value)
{
    if (bit > 7)
    {
        throw std::out_of_range("Bit position must be between 0 and 7.");
    }
    byte.setBit(bit, value);
}

uint8_t Register::readByte() const
{
    return byte.getByte();
}

uint8_t Register::readHighNibble() const
{
    return byte.getHighNibble();
}

uint8_t Register::readLowNibble() const
{
    return byte.getLowNibble();
}

bool Register::readBit(uint8_t bit) const
{
    if (bit > 7)
    {
        throw std::out_of_range("Bit position must be between 0 and 7.");
    }
    return byte.getBit(bit);
}

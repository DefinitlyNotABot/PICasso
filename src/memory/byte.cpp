#include "../../header/memory/byte.hpp"

Byte::Byte()
{
}

void Byte::setByte(uint8_t value)
{
    nibbles[0].setNibble(value & 0x0F);
    nibbles[1].setNibble((value >> 4) & 0x0F);
}

void Byte::setHighNibble(uint8_t value)
{
    nibbles[1].setNibble(value & 0x0F);
}

void Byte::setLowNibble(uint8_t value)
{
    nibbles[0].setNibble(value & 0x0F);
}

void Byte::setBit(uint8_t position, bool value)
{
    if (position < 4)
    {
        nibbles[0].setBit(position, value);
    }
    else if (position < 8)
    {
        nibbles[1].setBit(position - 4, value);
    }
}

uint8_t Byte::getByte() const
{
    return (nibbles[1].getNibble() << 4) | nibbles[0].getNibble();
}

uint8_t Byte::getHighNibble() const
{
    return nibbles[1].getNibble();
}

uint8_t Byte::getLowNibble() const
{
    return nibbles[0].getNibble();
}

bool Byte::getBit(uint8_t position) const
{
    if (position < 4)
    {
        return nibbles[0].getBit(position);
    }
    else if (position < 8)
    {
        return nibbles[1].getBit(position - 4);
    }
    return false;
}

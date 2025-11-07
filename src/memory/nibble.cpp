#include "../../header/memory/nibble.hpp"

Nibble::Nibble()
{
}

void Nibble::setNibble(uint8_t value)
{
    for (int i = 0; i < 4; ++i)
    {
        bits[i].setBit((value >> i) & 0x01);
    }
}

uint8_t Nibble::getNibble() const
{
    uint8_t value = 0;
    for (int i = 0; i < 4; ++i)
    {
        if (bits[i].getBit())
        {
            value |= (1 << i);
        }
    }
    return value;
}

void Nibble::setBit(uint8_t position, bool value)
{
    if (position < 4)
    {
        bits[position].setBit(value);
    }
}

bool Nibble::getBit(uint8_t position) const
{
    if (position < 4)
    {
        return bits[position].getBit();
    }
    return false;
}
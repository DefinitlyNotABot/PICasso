#include "../../header/memory/bit.hpp"

Bit::Bit() : bitValue(false)
{
}

void Bit::setBit(bool value)
{
    bitValue = value;
}

bool Bit::getBit() const
{
    return bitValue;
}

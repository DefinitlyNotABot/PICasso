#pragma once
#include "bit.hpp"
#include <cstdint>

class Nibble
{
private:
    Bit bits[4];

public:
    Nibble();

    void setNibble(uint8_t value);
    uint8_t getNibble() const;

    void setBit(uint8_t position, bool value);
    bool getBit(uint8_t position) const;
};

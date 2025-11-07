#pragma once
#include "nibble.hpp"
#include <cstdint>

class Byte
{
private:
    Nibble nibbles[2];

public:
    Byte();

    void setByte(uint8_t value);
    void setHighNibble(uint8_t value);
    void setLowNibble(uint8_t value);
    void setBit(uint8_t position, bool value);

    uint8_t getByte() const;
    uint8_t getHighNibble(Nibble &nibble) const;
    uint8_t getLowNibble(Nibble &nibble) const;
    bool getBit(uint8_t position) const;
};
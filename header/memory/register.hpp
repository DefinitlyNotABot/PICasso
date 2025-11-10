#pragma once
#include "byte.hpp"
#include <cstdint>

class Register
{
private:
    Byte byte;

public:
    Register();
    void writeByte(uint8_t value);
    void writeHighNibble(uint8_t value);
    void writeLowNibble(uint8_t value);
    void writeBit(uint8_t bit, bool value);

    uint8_t readByte() const;
    uint8_t readHighNibble() const;
    uint8_t readLowNibble() const;
    bool readBit(uint8_t bit) const;
};

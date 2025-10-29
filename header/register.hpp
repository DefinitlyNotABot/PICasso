#pragma once
#include <cstdint>

class Register
{
    private:
        uint8_t memory;

    public:
        Register();
        uint8_t readByte() const;
        uint8_t readHighNibble() const;
        uint8_t readLowNibble() const;
        bool readBit(uint8_t bit) const;
        
        void writeByte(uint8_t byte);
        void writeHighNibble(uint8_t byte);
        void writeLowNibble(uint8_t byte);
        void writeBit(uint8_t bit, bool value);
};

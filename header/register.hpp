#pragma once
#include <cstdint>

class Register
{
    private:
        uint8_t memory;

    public:
        Register();
        uint8_t getValue() const;
        uint8_t getHighByte() const;
        uint8_t getLowByte() const;
        
        void setByte(uint8_t byte);
        void setHighByte(uint8_t byte);
        void setLowByte(uint8_t byte);
};

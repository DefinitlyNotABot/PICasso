#pragma once
#include "register.hpp"

class Ram
{
    private:
    Register memory[256];

    public:
        Ram();
        uint8_t readRegister(uint8_t address);
        void writeRegister(uint8_t address, uint8_t value);   

};

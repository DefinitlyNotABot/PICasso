#pragma once
#include "register.hpp"

class Ram
{
    private:
    Register memory[255];

    public:
        Ram();
        uint8_t getRegister(uint8_t address);
        void setRegister(uint8_t address, uint8_t value);   

};

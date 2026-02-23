#pragma once

#include "instruction.hpp"

#define SET_ZERO_FLAG memoryInterface->writeStatusBit(MemoryInterface::StatusBits::Z, (result & 0xFF) == 0);

class Arithmetic : public virtual Instruction 
{
    protected:
        Logger logger = Logger("Arithmetic");
        uint8_t destination;
        uint8_t file;
        uint8_t fileValue;
        uint8_t WValue;
        void storeResult(uint16_t result);
        void loadCurrentValues();

         
    public:
        uint8_t getDestination();
        uint8_t getFile();
};

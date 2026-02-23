#pragma once

#include <cstdint>
#include <string>
#include <memory>

#include "memoryInterface.hpp"
#include "register.hpp"

class Instruction
{
    friend class PIC;
    protected:
        static std::shared_ptr<MemoryInterface> memoryInterface;
        static std::shared_ptr<Register> W;
        static uint8_t loadAddress(uint8_t address){
            if(address != 0) return address;
            return memoryInterface->readRegister(0x04);
        }
    public:
        virtual uint16_t execute() = 0;
        virtual std::string getName() = 0;
        virtual ~Instruction() = default;
        
};
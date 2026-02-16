#pragma once

#include <cstdint>
#include <string>
#include <memory>

#include "ram.hpp"

class Instruction
{
    friend class PIC;
    protected:
        static std::shared_ptr<Ram> ram;
    public:
        virtual uint16_t execute() = 0;
        virtual std::string getName() = 0;
        virtual ~Instruction() = default;
};
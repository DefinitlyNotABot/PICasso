#pragma once

#include <cstdint>
#include <string>
#include <memory>

#include "ram.hpp"
#include "register.hpp"

class Instruction
{
    friend class PIC;
    protected:
        static std::shared_ptr<Ram> ram;
        static std::shared_ptr<Register> W;
    public:
        virtual uint16_t execute() = 0;
        virtual std::string getName() = 0;
        virtual ~Instruction() = default;
};
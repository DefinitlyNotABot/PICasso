#pragma once

#include <cstdint>
#include <string>

class Instruction
{
    public:
        virtual uint16_t execute() = 0;
        virtual std::string getName() = 0;
        virtual ~Instruction() = default;
};
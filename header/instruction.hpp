#pragma once

#include <cstdint>


class Instruction
{
    public:
        virtual uint16_t execute() = 0;
        virtual ~Instruction() = default;
};
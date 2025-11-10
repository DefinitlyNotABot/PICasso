#pragma once

#include <cstdint>


class Instruction
{
    enum Type{
        ARITHMETIC,
        BITWISE,
        LITERAL,
    };

    private:
        uint16_t type;
    public:
        virtual uint16_t execute() = 0;
};
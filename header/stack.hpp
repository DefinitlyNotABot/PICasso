#pragma once

#include "register.hpp"
#include "logger.hpp"

class Stack
{
    private:
        uint8_t stack[8];
        uint8_t stackPointer;
        Logger logger{"Stack"};

    public:
        Stack();
        ~Stack() = default;

        void push(uint8_t value);
        uint8_t pop();
        void reset();
};
#include "stack.hpp"

Stack::Stack()
{
    reset();
}

void Stack::push(uint8_t value)
{
    if(stackPointer >= 8)
    {
        logger.log(std::string("Stack overflow"), Logger::LogLevel::WARNING);
    }
    stack[stackPointer] = value;
    stackPointer = (stackPointer + 1) % 8;
}

uint8_t Stack::pop()
{
    if(stackPointer == 0)
    {
        logger.log(std::string("Stack underflow"), Logger::LogLevel::WARNING);
    }
    stackPointer = (stackPointer - 1 + 8) % 8; // -1 to move back, +8 to handle negative wrap-around, %8 to wrap around
    return stack[stackPointer];
}

void Stack::reset()
{
    stackPointer = 0;
    for(int i = 0; i < 8; i++)
    {
        stack[i] = 0;
    }
}

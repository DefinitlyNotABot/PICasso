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
    stack[stackPointer++ % 8] = value;
}

uint8_t Stack::pop()
{
    if(stackPointer == 0)
    {
        logger.log(std::string("Stack underflow"), Logger::LogLevel::WARNING);
    }
    return stack[--stackPointer % 8]; // Wrap around if stack pointer goes below 0
}

void Stack::reset()
{
    stackPointer = 0;
    for(int i = 0; i < 8; i++)
    {
        stack[i] = 0;
    }
}

#pragma once

#include <cstdint>
#include <memory>

#include "memoryInterface.hpp"

class Prescaler
{
    private:
        uint16_t prescaleCounter;

        std::shared_ptr<MemoryInterface> memoryInterface;

    public:
        enum Source{
            TMR0 = 0,
            WDT = 1
        };
        Prescaler();
        Prescaler(std::shared_ptr<MemoryInterface> memoryInterface);
        ~Prescaler();

        int step(Source source);
        void reset();
};

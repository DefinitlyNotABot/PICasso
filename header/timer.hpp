#pragma once

#include <memory>
#include "prescaler.hpp"
#include "memoryInterface.hpp"

class Timer
{
    private:
        std::shared_ptr<Prescaler> prescaler;
        std::shared_ptr<MemoryInterface> memoryInterface;

    public:
        Timer() = default;
        Timer(std::shared_ptr<Prescaler> prescaler, std::shared_ptr<MemoryInterface> memoryInterface);
        ~Timer();

        void timeStep();


};
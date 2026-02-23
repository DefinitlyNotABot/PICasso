#pragma once

#include "pic.hpp"

#include <atomic>
#include <cstdint>
#include <mutex>
#include <string>

struct SimulationState {
    std::atomic<bool> quit{false};
    std::atomic<bool> runMode{false};
    std::atomic<bool> dashMode{false};
    std::atomic<bool> stepRequested{false};
    std::atomic<uint64_t> executedSteps{0};
    std::atomic<uint64_t> programTimeUs{0};

    std::mutex statusMutex;
    std::string statusMessage;
    std::string loadedProgramPath;
};

class TerminalUI {
public:
    void run(PIC& pic, SimulationState& state);
};

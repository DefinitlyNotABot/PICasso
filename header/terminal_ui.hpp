#pragma once

#include "pic.hpp"

#include <atomic>
#include <cstdint>
#include <memory>
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
    TerminalUI();
    ~TerminalUI();

    TerminalUI(const TerminalUI&) = delete;
    TerminalUI& operator=(const TerminalUI&) = delete;
    TerminalUI(TerminalUI&&) = delete;
    TerminalUI& operator=(TerminalUI&&) = delete;

    void run(PIC& pic, SimulationState& state);

private:
    class Renderer;
    class Controller;

    std::unique_ptr<Renderer> renderer;
    std::unique_ptr<Controller> controller;
};

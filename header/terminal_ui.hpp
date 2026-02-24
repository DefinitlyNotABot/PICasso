#pragma once

#include "pic.hpp"
#include "tui_initializer.hpp"
#include "tui_types.hpp"
#include "tui_controller.hpp"
#include "tui_renderer.hpp"

#include <atomic>
#include <cstdint>
#include <memory>
#include <mutex>
#include <string>
#include "tui_shareddata.hpp"


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
    std::shared_ptr<TUI_SharedData> sharedData = std::make_shared<TUI_SharedData>();

    std::unique_ptr<TUI_Renderer> renderer;
    std::unique_ptr<TUI_Controller> controller;
    std::unique_ptr<TUIInitializer> tuiInitializer;
};

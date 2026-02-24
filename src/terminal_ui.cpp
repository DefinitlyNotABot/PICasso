#include "terminal_ui.hpp"
#include "tui_types.hpp"

#include <array>
#include <cctype>
#include <chrono>
#include <cstdarg>
#include <curses.h>
#include <exception>
#include <fstream>
#include <iomanip>
#include <optional>
#include <sstream>
#include <string>
#include <thread>
#include <vector>
#include <tui_layout.hpp>
#include <tui_helper.hpp>

namespace {


std::vector<std::string> loadFileLines(const std::string& filePath)
{
    std::vector<std::string> lines;
    if (filePath.empty())
    {
        return lines;
    }

    std::ifstream input(filePath);
    if (!input.is_open())
    {
        return lines;
    }

    std::string line;
    while (std::getline(input, line))
    {
        if (!line.empty() && line.back() == '\r')
        {
            line.pop_back();
        }
        lines.push_back(line);
    }

    return lines;
}



} // namespace

TerminalUI::TerminalUI()
    : renderer(std::make_unique<TUI_Renderer>()),
      controller(std::make_unique<TUI_Controller>()),
      tuiInitializer(std::make_unique<TUIInitializer>())
{
}

TerminalUI::~TerminalUI() = default;

void TerminalUI::run(PIC& pic, SimulationState& state)
{
    tuiInitializer->initialize();

    
    std::optional<uint8_t> pendingRamEditAddress;
    std::string shownFilePath;
    std::vector<std::string> shownFileLines;
    int asmManualScrollStart = 0;
    bool asmManualScrollEnabled = false;
    int asmRenderedStart = 0;
    PICSnapshot snapshot;

    while (!state.quit.load())
    {
        pic.getSnapshot(snapshot);
        std::vector<HitBox> hitBoxes;

        erase();

        std::string loadedPath;
        {
            std::lock_guard<std::mutex> lock(state.statusMutex);
            loadedPath = state.loadedProgramPath;
        }

        if (loadedPath != shownFilePath)
        {
            shownFilePath = loadedPath;
            shownFileLines = loadFileLines(shownFilePath);
            asmManualScrollStart = 0;
            asmManualScrollEnabled = false;
        }

        renderer->draw(snapshot,
                       state,
                       pendingRamEditAddress,
                       loadedPath,
                       shownFileLines,
                       asmManualScrollStart,
                       asmManualScrollEnabled,
                       &asmRenderedStart,
                       hitBoxes);

        if (state.runMode.load())
        {
            state.stepRequested.store(true);
        }

        refresh();

        if (controller->handlePendingMemoryEdit(pic, state, pendingRamEditAddress))
        {
            continue;
        }

        int ch = getch();
        if (ch == ERR)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(1));
            continue;
        }

        if (controller->handleKeyPress(ch, state))
        {
            break;
        }

        if (ch == KEY_MOUSE)
        {
            MEVENT event;
            if (getmouse(&event) == OK)
            {
                controller->handleMouseEvent(pic,
                                             state,
                                             event,
                                             hitBoxes,
                                             pendingRamEditAddress,
                                             asmManualScrollStart,
                                             asmManualScrollEnabled,
                                             asmRenderedStart,
                                             shownFileLines);
            }
        }
    }

    endwin();
}

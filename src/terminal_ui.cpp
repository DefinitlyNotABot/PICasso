#include "terminal_ui.hpp"
#include "tui_types.hpp"
#include "tui_layout.hpp"
#include "tui_helper.hpp"

#include <cctype>
#include <chrono>
#include <fstream>
#include <string>
#include <thread>
#include <vector>


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
    : renderer(std::make_unique<TUI_Renderer>(sharedData)),
      controller(std::make_unique<TUI_Controller>(sharedData)),
      tuiInitializer(std::make_unique<TUIInitializer>())
{
}

TerminalUI::~TerminalUI() = default;

void TerminalUI::run(PIC& pic, SimulationState& state)
{
    tuiInitializer->initialize();    

    while (!state.quit.load())
    {
        pic.getSnapshot(sharedData->getSnapshotReference());
        std::vector<HitBox> hitBoxes;

        erase();

        std::string loadedPath;
        {
            std::lock_guard<std::mutex> lock(state.statusMutex);
            loadedPath = state.loadedProgramPath;
        }

        if (loadedPath != sharedData->getShownFilePath())
        {
            sharedData->getShownFilePath() = loadedPath;
            sharedData->getShownFileLines() = loadFileLines(sharedData->getShownFilePath());
            sharedData->getAsmManualScrollStart() = 0;
            sharedData->getAsmManualScrollEnabled() = false;
        }

        renderer->draw(state, loadedPath, hitBoxes);

        if (state.runMode.load())
        {
            state.stepRequested.store(true);
        }

        refresh();

        if (controller->handlePendingMemoryEdit(pic, state, sharedData->getPendingRamEditAddress()))
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
                controller->handleMouseEvent(pic, state, event, hitBoxes);
            }
        }
    }

}

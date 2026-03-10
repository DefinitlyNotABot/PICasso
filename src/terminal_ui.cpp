#include "terminal_ui.hpp"
#include "tui_types.hpp"
#include "tui_layout.hpp"
#include "tui_helper.hpp"
#include "lst_preview.hpp"

#include <cctype>
#include <chrono>
#include <string>
#include <thread>
#include <vector>

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
            sharedData->getShownFileLines() = LstPreview::loadFileLines(sharedData->getShownFilePath());
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

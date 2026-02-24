#include "tui_controller.hpp"

bool TUI_Controller::handlePendingMemoryEdit(PIC& pic,
                                              SimulationState& state,
                                              std::optional<uint8_t>& pendingRamEditAddress) const
{
if (!pendingRamEditAddress.has_value())
{
    return false;
}

handleMemoryEdit(pic, state, pendingRamEditAddress.value());
pendingRamEditAddress.reset();
return true;
}

bool TUI_Controller::handleKeyPress(int ch, SimulationState& state) const
{
    if (ch == 'q' || ch == 'Q')
    {
        state.quit.store(true);
        return true;
    }

    return false;
}

void TUI_Controller::handleMouseEvent(PIC& pic,
                          SimulationState& state,
                          const MEVENT& event,
                          const std::vector<HitBox>& hitBoxes) const
{
    if (event.bstate & BUTTON4_PRESSED)
    {
        if (TUI_Helper::isInAsmPanel(event.y, event.x))
        {
            if (!sharedData->getAsmManualScrollEnabled())
            {
                sharedData->getAsmManualScrollStart() = sharedData->getAsmRenderedStart();
            }
            sharedData->getAsmManualScrollEnabled() = true;
            sharedData->getAsmManualScrollStart() = TUI_Helper::clampAsmScrollStart(sharedData->getAsmManualScrollStart() - 1, static_cast<int>(sharedData->getShownFileLines().size()));
        }
        return;
    }

    if (event.bstate & BUTTON5_PRESSED)
    {
        if (TUI_Helper::isInAsmPanel(event.y, event.x))
        {
            if (!sharedData->getAsmManualScrollEnabled())
            {
                sharedData->getAsmManualScrollStart() = sharedData->getAsmRenderedStart();
            }
            sharedData->getAsmManualScrollEnabled() = true;
            sharedData->getAsmManualScrollStart() = TUI_Helper::clampAsmScrollStart(sharedData->getAsmManualScrollStart() + 1, static_cast<int>(sharedData->getShownFileLines().size()));
        }
        return;
    }

    if ((event.bstate & BUTTON1_CLICKED) || (event.bstate & BUTTON1_PRESSED))
    {
        for (const HitBox& hit : hitBoxes)
        {
            if (TUI_Helper::contains(hit, event.y, event.x))
            {
                processHit(pic, state, hit, sharedData->getPendingRamEditAddress());
                break;
            }
        }
    }
}

void TUI_Controller::handleLoadFile(PIC& pic, SimulationState& state)
{
    auto text = TUI_Helper::promptInput("File path: ");
    if (!text || text->empty())
    {
        TUI_Helper::setStatus(state, "Load canceled");
        return;
    }

    try
    {
        pic.loadProgram(*text);
        pic.reset();
        state.executedSteps.store(0);
        state.programTimeUs.store(0);
        {
            std::lock_guard<std::mutex> lock(state.statusMutex);
            state.loadedProgramPath = *text;
            state.statusMessage = "Loaded file " + *text;
        }
    }
    catch (const std::exception& ex)
    {
        TUI_Helper::setStatus(state, std::string("Load failed: ") + ex.what());
    }
}

void TUI_Controller::handleMemoryEdit(PIC& pic, SimulationState& state, uint8_t address)
{
    auto text = TUI_Helper::promptInput("Hex value (00-FF): ");
    if (!text)
    {
        TUI_Helper::setStatus(state, "Edit canceled");
        return;
    }

    uint8_t value = 0;
    if (!TUI_Helper::parseHexByte(*text, value))
    {
        TUI_Helper::setStatus(state, "Invalid hex value");
        return;
    }

    std::string errorMessage;
    if (!pic.tryWriteRegister(address, value, &errorMessage))
    {
        TUI_Helper::setStatus(state, "Write failed: " + errorMessage);
        return;
    }

    TUI_Helper::setStatus(state, "Wrote 0x" + TUI_Helper::toHex2(value) + " to 0x" + TUI_Helper::toHex2(address));
}


void TUI_Controller::handleToggleBit(PIC& pic, SimulationState& state, uint8_t address, uint8_t bit)
{
    std::string errorMessage;
    if (!pic.tryToggleBit(address, bit, &errorMessage))
    {
        TUI_Helper::setStatus(state, "Toggle failed: " + errorMessage);
        return;
    }

    TUI_Helper::setStatus(state, "Toggled bit " + std::to_string(bit) + " at 0x" + TUI_Helper::toHex2(address));
}

void TUI_Controller::processHit(PIC& pic,
                           SimulationState& state,
                           const HitBox& hit,
                           std::optional<uint8_t>& pendingRamEditAddress)
{
    switch (hit.type)
    {
    case HitType::MemoryCell:
        pendingRamEditAddress = hit.address;
        break;
    case HitType::ToggleBit:
        handleToggleBit(pic, state, hit.address, hit.bit);
        break;
    case HitType::StepButton:
        state.runMode.store(false);
        state.dashMode.store(false);
        state.stepRequested.store(true);
        TUI_Helper::setStatus(state, "Single step requested");
        break;
    case HitType::RunButton:
        state.runMode.store(!state.runMode.load());
        if (state.runMode.load())
        {
            state.dashMode.store(false);
        }
        TUI_Helper::setStatus(state, state.runMode.load() ? "Running" : "Paused");
        break;
    case HitType::DashButton:
        state.dashMode.store(!state.dashMode.load());
        if (state.dashMode.load())
        {
            state.runMode.store(false);
        }
        TUI_Helper::setStatus(state, state.dashMode.load() ? "Dash mode: backend running freely" : "Dash stopped");
        break;
    case HitType::ResetButton:
        state.runMode.store(false);
        state.dashMode.store(false);
        pic.reset();
        state.executedSteps.store(0);
        state.programTimeUs.store(0);
        TUI_Helper::setStatus(state, "PIC reset");
        break;
    case HitType::LoadButton:
        state.runMode.store(false);
        state.dashMode.store(false);
        handleLoadFile(pic, state);
        break;
    case HitType::QuitButton:
        state.runMode.store(false);
        state.dashMode.store(false);
        state.quit.store(true);
        TUI_Helper::setStatus(state, "Quitting...");
        break;
    }
}
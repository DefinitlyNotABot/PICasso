#pragma once

#include "pic.hpp"
#include "tui_types.hpp"
#include <curses.h>
#include "tui_helper.hpp"

class TUI_Controller {
public:
    bool handlePendingMemoryEdit(PIC& pic,
                                 SimulationState& state,
                                 std::optional<uint8_t>& pendingRamEditAddress) const;

    bool handleKeyPress(int ch, SimulationState& state) const;

    void handleMouseEvent(PIC& pic,
                          SimulationState& state,
                          const MEVENT& event,
                          const std::vector<HitBox>& hitBoxes,
                          std::optional<uint8_t>& pendingRamEditAddress,
                          int& asmManualScrollStart,
                          bool& asmManualScrollEnabled,
                          int asmRenderedStart,
                          const std::vector<std::string>& shownFileLines) const;

private:

        static void handleLoadFile(PIC& pic, SimulationState& state);

        static void handleMemoryEdit(PIC& pic, SimulationState& state, uint8_t address);

        static void handleToggleBit(PIC& pic, SimulationState& state, uint8_t address, uint8_t bit);

        static void processHit(PIC& pic,
                            SimulationState& state,
                            const HitBox& hit,
                            std::optional<uint8_t>& pendingRamEditAddress);
};
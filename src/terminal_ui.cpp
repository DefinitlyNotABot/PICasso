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




void printWithColor(int y, int x, short pair, int attrs, const char* format, ...)
{
    int flags = attrs;
    if (1)
    {
        flags |= COLOR_PAIR(pair);
    }

    if (flags != 0)
    {
        attron(flags);
    }

    move(y, x);
    va_list args;
    va_start(args, format);
    vw_printw(stdscr, format, args);
    va_end(args);

    if (flags != 0)
    {
        attroff(flags);
    }
}

short statusPairFromText(const std::string& status)
{
    std::string lowered = status;
    for (char& c : lowered)
    {
        c = static_cast<char>(std::tolower(static_cast<unsigned char>(c)));
    }

    if (lowered.find("error") != std::string::npos || lowered.find("failed") != std::string::npos ||
        lowered.find("halt") != std::string::npos)
    {
        return CP_STATUS_ERR;
    }

    if (lowered.find("cancel") != std::string::npos || lowered.find("invalid") != std::string::npos)
    {
        return CP_STATUS_WARN;
    }

    return CP_STATUS_OK;
}





std::string getStatus(SimulationState& state)
{
    std::lock_guard<std::mutex> lock(state.statusMutex);
    return state.statusMessage;
}

void addBitWidget(std::vector<HitBox>& hitBoxes, int y, int x, bool value, uint8_t address, uint8_t bit)
{
    printWithColor(y, x, value ? CP_BIT_ON : CP_BIT_OFF, A_BOLD, "[%d]", value ? 1 : 0);
    hitBoxes.push_back(HitBox{y, x, 3, 1, HitType::ToggleBit, address, bit});
}


bool parseLstInstructionIndex(const std::string& line, uint16_t& index)
{
    if (line.size() < 4)
    {
        return false;
    }

    const std::string token = line.substr(0, 4);
    for (char c : token)
    {
        if (!std::isxdigit(static_cast<unsigned char>(c)))
        {
            return false;
        }
    }

    index = static_cast<uint16_t>(std::stoul(token, nullptr, 16));
    return true;
}




int findFirstCodeLineIndex(const std::vector<std::string>& fileLines)
{
    for (int i = 0; i < static_cast<int>(fileLines.size()); ++i)
    {
        uint16_t lstIndex = 0;
        if (parseLstInstructionIndex(fileLines[static_cast<size_t>(i)], lstIndex))
        {
            return i;
        }
    }
    return 0;
}

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

class TerminalUI::Renderer {
public:
    void draw(const PICSnapshot& snapshot,
              SimulationState& state,
              const std::optional<uint8_t>& selectedRamAddress,
              const std::string& loadedPath,
              const std::vector<std::string>& shownFileLines,
              int asmManualScrollStart,
              bool asmManualScrollEnabled,
              int* asmRenderedStart,
              std::vector<HitBox>& hitBoxes) const
    {
        int maxY = 0;
        int maxX = 0;
        getmaxyx(stdscr, maxY, maxX);

        if (maxY < TUI_Layout::kRequiredTerminalHeight || maxX < TUI_Layout::kRequiredTerminalWidth)
        {
            printWithColor(0, 0, CP_STATUS_WARN, A_BOLD, "Terminal too small. Need at least %dx%d.", TUI_Layout::kRequiredTerminalWidth, TUI_Layout::kRequiredTerminalHeight);
            printWithColor(1, 0, CP_STATUS_WARN, 0, "Current: %dx%d", maxX, maxY);
            return;
        }

        drawTopBits(snapshot, hitBoxes);
        drawMemoryGrid(snapshot, hitBoxes, selectedRamAddress);
        const bool preferTopOffset = !asmManualScrollEnabled && state.executedSteps.load() == 0;
        drawAsmPanel(snapshot, shownFileLines, asmManualScrollStart, asmManualScrollEnabled, preferTopOffset, asmRenderedStart);
        drawControlPanel(state, hitBoxes);

        if (!loadedPath.empty())
        {
            printWithColor(30, 0, CP_LABEL, 0, "Loaded: %s", loadedPath.c_str());
        }

        printWithColor(31, 0, CP_LABEL, 0, "Controls: Click [load file], [ STEP ], [ RUN/STOP ], [ DASH/HALT ], [ RESET ], [ QUIT ]");
        const std::string status = getStatus(state);
        printWithColor(32, 0, statusPairFromText(status), A_BOLD, "Status: %s", status.c_str());
    }

private:
    static void drawTopBits(const PICSnapshot& snapshot, std::vector<HitBox>& hitBoxes)
    {
        printWithColor(0, 0, CP_HEADER, A_BOLD, "SFR:                          IRP  RP1  RP0   TO   PD   Z    DC   C");
        printWithColor(1, 0, CP_LABEL, 0, "                              ");

        for (int bit = 7; bit >= 0; --bit)
        {
            int x = 30 + (7 - bit) * 5;
            bool value = snapshot.validMemory[0x03] ? ((snapshot.memory[0x03] >> bit) & 1U) != 0U : false;
            addBitWidget(hitBoxes, 1, x, value, 0x03, static_cast<uint8_t>(bit));
        }

        printWithColor(2, 0, CP_VALUE, A_BOLD, "  W-Reg: %s   PC: %s", TUI_Helper::toHex2(snapshot.w).c_str(), TUI_Helper::toHex2(snapshot.programCounter).c_str());
        printWithColor(3, 0, CP_VALUE, 0, "  FSR:   %s   Stack: --", snapshot.validMemory[0x04] ? TUI_Helper::toHex2(snapshot.memory[0x04]).c_str() : "--");
        printWithColor(4, 0, CP_VALUE, 0, "  PCL:   %s   VT:    --", snapshot.validMemory[0x02] ? TUI_Helper::toHex2(snapshot.memory[0x02]).c_str() : "--");
        printWithColor(5, 0, CP_VALUE, 0, "  PCLATH:%s   WDT:   --", snapshot.validMemory[0x0A] ? TUI_Helper::toHex2(snapshot.memory[0x0A]).c_str() : "--");
        printWithColor(6, 0, CP_VALUE, 0, "  Status:%s", snapshot.validMemory[0x03] ? TUI_Helper::toHex2(snapshot.memory[0x03]).c_str() : "--");

        printWithColor(3, 30, CP_LABEL, 0, "RBP IntE T0CS T0SE  PSA  PS2  PS1  PS0");
        for (int bit = 7; bit >= 0; --bit)
        {
            int x = 30 + (7 - bit) * 5;
            bool value = snapshot.validMemory[0x81] ? ((snapshot.memory[0x81] >> bit) & 1U) != 0U : false;
            addBitWidget(hitBoxes, 4, x, value, 0x81, static_cast<uint8_t>(bit));
        }

        printWithColor(6, 30, CP_LABEL, 0, "GIE EEIE T0IE INTE RBIE T0IF INTF RBIF");
        for (int bit = 7; bit >= 0; --bit)
        {
            int x = 30 + (7 - bit) * 5;
            bool value = snapshot.validMemory[0x0B] ? ((snapshot.memory[0x0B] >> bit) & 1U) != 0U : false;
            addBitWidget(hitBoxes, 7, x, value, 0x0B, static_cast<uint8_t>(bit));
        }

        printWithColor(0, 75, CP_HEADER, A_BOLD, "|  RA    7   6   5   4   3   2   1   0");
        printWithColor(1, 75, CP_LABEL, 0, "|  TRIS");
        for (int bit = 7; bit >= 0; --bit)
        {
            int x = 84 + (7 - bit) * 4;
            bool value = snapshot.validMemory[0x85] ? ((snapshot.memory[0x85] >> bit) & 1U) != 0U : false;
            addBitWidget(hitBoxes, 1, x, value, 0x85, static_cast<uint8_t>(bit));
        }

        printWithColor(2, 75, CP_LABEL, 0, "|  PIN ");
        for (int bit = 7; bit >= 0; --bit)
        {
            int x = 84 + (7 - bit) * 4;
            bool value = snapshot.validMemory[0x05] ? ((snapshot.memory[0x05] >> bit) & 1U) != 0U : false;
            addBitWidget(hitBoxes, 2, x, value, 0x05, static_cast<uint8_t>(bit));
        }

        printWithColor(4, 75, CP_HEADER, A_BOLD, "|  RB    7   6   5   4   3   2   1   0");
        printWithColor(5, 75, CP_LABEL, 0, "|  TRIS");
        for (int bit = 7; bit >= 0; --bit)
        {
            int x = 84 + (7 - bit) * 4;
            bool value = snapshot.validMemory[0x86] ? ((snapshot.memory[0x86] >> bit) & 1U) != 0U : false;
            addBitWidget(hitBoxes, 5, x, value, 0x86, static_cast<uint8_t>(bit));
        }

        printWithColor(6, 75, CP_LABEL, 0, "|  PIN ");
        for (int bit = 7; bit >= 0; --bit)
        {
            int x = 84 + (7 - bit) * 4;
            bool value = snapshot.validMemory[0x06] ? ((snapshot.memory[0x06] >> bit) & 1U) != 0U : false;
            addBitWidget(hitBoxes, 6, x, value, 0x06, static_cast<uint8_t>(bit));
        }
    }

    static void drawMemoryGrid(const PICSnapshot& snapshot, std::vector<HitBox>& hitBoxes, const std::optional<uint8_t>& selectedRamAddress)
    {
        static const std::array<uint8_t, 20> rowBases = {
            0x00, 0x08, 0x10, 0x18, 0x20, 0x28, 0x30, 0x38, 0x40, 0x48,
            0x80, 0x88, 0x90, 0x98, 0xA0, 0xA8, 0xB0, 0xB8, 0xC0, 0xC8};

        printWithColor(9, 3, CP_HEADER, A_BOLD, "00 01 02 03 04 05 06 07");
        for (int row = 0; row < static_cast<int>(rowBases.size()); ++row)
        {
            int y = 10 + row;
            uint8_t base = rowBases[row];
            printWithColor(y, 0, CP_LABEL, A_BOLD, "%s", TUI_Helper::toHex2(base).c_str());

            for (int col = 0; col < 8; ++col)
            {
                uint8_t address = static_cast<uint8_t>(base + col);
                int x = 3 + col * 3;
                std::string cell = snapshot.validMemory[address] ? TUI_Helper::toHex2(snapshot.memory[address]) : "--";
                const bool isSelected = selectedRamAddress.has_value() && selectedRamAddress.value() == address;
                const short pair = isSelected ? CP_SELECTED_FIELD : (snapshot.validMemory[address] ? CP_VALUE : CP_INVALID);
                const int attrs = isSelected ? A_BOLD : 0;
                printWithColor(y, x, pair, attrs, "%s", cell.c_str());
                hitBoxes.push_back(HitBox{y, x, 2, 1, HitType::MemoryCell, address, 0});
            }
        }
    }

    static void drawAsmPanel(const PICSnapshot& snapshot,
                             const std::vector<std::string>& fileLines,
                             int manualScrollStart,
                             bool manualScrollEnabled,
                             bool preferTopOffset,
                             int* renderedStart)
    {
        int left = TUI_Layout::kAsmPanelLeft;
        int top = TUI_Layout::kAsmPanelTop;
        constexpr int asmTextWidth = TUI_Layout::kAsmTextWidth;

        printWithColor(top, left, CP_HEADER, A_BOLD, "ASM code");

        uint16_t pc = snapshot.programCounter;

        int currentFileLine = 0;
        bool foundCurrentLine = false;
        for (int i = 0; i < static_cast<int>(fileLines.size()); ++i)
        {
            uint16_t lstIndex = 0;
            if (parseLstInstructionIndex(fileLines[static_cast<size_t>(i)], lstIndex) && lstIndex == pc)
            {
                currentFileLine = i;
                foundCurrentLine = true;
                break;
            }
        }

        int maxRows = TUI_Layout::kAsmVisibleRows;
        int start = 0;
        if (manualScrollEnabled)
        {
            start = TUI_Helper::clampAsmScrollStart(manualScrollStart, static_cast<int>(fileLines.size()));
        }
        else if (preferTopOffset)
        {
            start = findFirstCodeLineIndex(fileLines);
        }
        else if (foundCurrentLine && currentFileLine > 5)
        {
            start = currentFileLine - 5;
        }

        start = TUI_Helper::clampAsmScrollStart(start, static_cast<int>(fileLines.size()));
        if (renderedStart != nullptr)
        {
            *renderedStart = start;
        }

        for (int row = 0; row < maxRows; ++row)
        {
            int lineIndex = start + row;
            int y = top + 1 + row;
            int displayLineNumber = lineIndex + 1;

            if (lineIndex >= static_cast<int>(fileLines.size()))
            {
                printWithColor(y, left, CP_LABEL, 0, "%3d|", displayLineNumber);
                continue;
            }

            std::string lineText = fileLines[static_cast<size_t>(lineIndex)];

            uint16_t lstIndex = 0;
            const bool indexAvailable = parseLstInstructionIndex(lineText, lstIndex);
            const bool isCurrentInstruction = indexAvailable && lstIndex == pc;

            const char* marker = isCurrentInstruction ? ">" : " ";
            const short linePair = isCurrentInstruction ? CP_HIGHLIGHT : CP_VALUE;
            const int lineAttr = isCurrentInstruction ? A_BOLD : 0;
            printWithColor(y, left, linePair, lineAttr, "%3d%s| %-*.*s", displayLineNumber, marker, asmTextWidth, asmTextWidth, lineText.c_str());
        }
    }

    static void drawControlPanel(const SimulationState& state, std::vector<HitBox>& hitBoxes)
    {
        int x = TUI_Layout::kControlPanelLeft;
        printWithColor(9, x, CP_BUTTON, A_BOLD, "[load file]");
        hitBoxes.push_back(HitBox{9, x, 11, 1, HitType::LoadButton, 0, 0});

        printWithColor(9, x + 13, CP_HEADER, A_BOLD, "| Sim Controls:");
        printWithColor(11, x + 13, CP_LABEL, 0, "Program Time:");
        printWithColor(12, x + 13, CP_VALUE, A_BOLD, "%llu us", static_cast<unsigned long long>(state.programTimeUs.load()));

        printWithColor(14, x + 13, CP_BUTTON, A_BOLD, "[ STEP  ]");
        hitBoxes.push_back(HitBox{14, x + 13, 8, 1, HitType::StepButton, 0, 0});

        const bool running = state.runMode.load();
        printWithColor(15, x + 13, running ? CP_BUTTON_DANGER : CP_BUTTON_ACTIVE, A_BOLD, running ? "[ STOP  ]" : "[ RUN   ]");
        hitBoxes.push_back(HitBox{15, x + 13, 8, 1, HitType::RunButton, 0, 0});

        const bool dashing = state.dashMode.load();
        printWithColor(16, x + 13, dashing ? CP_BUTTON_DANGER : CP_BUTTON_ACTIVE, A_BOLD, dashing ? "[ HALT  ]" : "[ DASH  ]");
        hitBoxes.push_back(HitBox{16, x + 13, 8, 1, HitType::DashButton, 0, 0});

        printWithColor(17, x + 13, CP_STATUS_WARN, A_BOLD, "[ RESET ]");
        hitBoxes.push_back(HitBox{17, x + 13, 8, 1, HitType::ResetButton, 0, 0});

        printWithColor(18, x + 13, CP_BUTTON_DANGER, A_BOLD, "[ QUIT  ]");
        hitBoxes.push_back(HitBox{18, x + 13, 8, 1, HitType::QuitButton, 0, 0});

        printWithColor(19, x + 13, CP_LABEL, 0, "Steps: %llu", static_cast<unsigned long long>(state.executedSteps.load()));
    }
};



TerminalUI::TerminalUI()
    : renderer(std::make_unique<Renderer>()),
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

#include "terminal_ui.hpp"

#include <array>
#include <cctype>
#include <chrono>
#include <curses.h>
#include <exception>
#include <iomanip>
#include <optional>
#include <sstream>
#include <string>
#include <thread>
#include <vector>

namespace {

enum class HitType {
    MemoryCell,
    ToggleBit,
    StepButton,
    RunButton,
    ResetButton,
    LoadButton
};

struct HitBox {
    int y;
    int x;
    int width;
    int height;
    HitType type;
    uint8_t address;
    uint8_t bit;
};

std::string toHex2(uint8_t value)
{
    std::ostringstream oss;
    oss << std::uppercase << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(value);
    return oss.str();
}

bool contains(const HitBox& hit, int y, int x)
{
    return y >= hit.y && y < hit.y + hit.height && x >= hit.x && x < hit.x + hit.width;
}

void setStatus(SimulationState& state, const std::string& message)
{
    std::lock_guard<std::mutex> lock(state.statusMutex);
    state.statusMessage = message;
}

std::string getStatus(SimulationState& state)
{
    std::lock_guard<std::mutex> lock(state.statusMutex);
    return state.statusMessage;
}

void addBitWidget(std::vector<HitBox>& hitBoxes, int y, int x, bool value, uint8_t address, uint8_t bit)
{
    mvprintw(y, x, "[%d]", value ? 1 : 0);
    hitBoxes.push_back(HitBox{y, x, 3, 1, HitType::ToggleBit, address, bit});
}

bool parseHexByte(const std::string& text, uint8_t& output)
{
    if (text.empty() || text.size() > 2)
    {
        return false;
    }

    for (char c : text)
    {
        if (!std::isxdigit(static_cast<unsigned char>(c)))
        {
            return false;
        }
    }

    unsigned long value = std::stoul(text, nullptr, 16);
    if (value > 0xFF)
    {
        return false;
    }

    output = static_cast<uint8_t>(value);
    return true;
}

std::optional<std::string> promptInput(const std::string& prompt)
{
    int maxY = 0;
    int maxX = 0;
    getmaxyx(stdscr, maxY, maxX);

    move(maxY - 2, 0);
    clrtoeol();
    mvprintw(maxY - 2, 0, "%s", prompt.c_str());

    char input[256] = {0};
    nodelay(stdscr, FALSE);
    echo();
    curs_set(1);
    int rc = getnstr(input, static_cast<int>(sizeof(input) - 1));
    noecho();
    curs_set(0);
    nodelay(stdscr, TRUE);

    if (rc == ERR)
    {
        return std::nullopt;
    }

    return std::string(input);
}

void drawTopBits(const PICSnapshot& snapshot, std::vector<HitBox>& hitBoxes)
{
    mvprintw(0, 0, "SFR:                          IRP  RP1  RP0   TO   PD   Z    DC   C");
    mvprintw(1, 0, "                              ");

    for (int bit = 7; bit >= 0; --bit)
    {
        int x = 30 + (7 - bit) * 5;
        bool value = snapshot.validMemory[0x03] ? ((snapshot.memory[0x03] >> bit) & 1U) != 0U : false;
        addBitWidget(hitBoxes, 1, x, value, 0x03, static_cast<uint8_t>(bit));
    }

    mvprintw(2, 0, "  W-Reg: %s   PC: %s", toHex2(snapshot.w).c_str(), toHex2(snapshot.programCounter).c_str());
    mvprintw(3, 0, "  FSR:   %s   Stack: --", snapshot.validMemory[0x04] ? toHex2(snapshot.memory[0x04]).c_str() : "--");
    mvprintw(4, 0, "  PCL:   %s   VT:    --", snapshot.validMemory[0x02] ? toHex2(snapshot.memory[0x02]).c_str() : "--");
    mvprintw(5, 0, "  PCLATH:%s   WDT:   --", snapshot.validMemory[0x0A] ? toHex2(snapshot.memory[0x0A]).c_str() : "--");
    mvprintw(6, 0, "  Status:%s", snapshot.validMemory[0x03] ? toHex2(snapshot.memory[0x03]).c_str() : "--");

    mvprintw(3, 30, "RBP IntE T0CS T0SE  PSA  PS2  PS1  PS0");
    for (int bit = 7; bit >= 0; --bit)
    {
        int x = 30 + (7 - bit) * 5;
        bool value = snapshot.validMemory[0x81] ? ((snapshot.memory[0x81] >> bit) & 1U) != 0U : false;
        addBitWidget(hitBoxes, 4, x, value, 0x81, static_cast<uint8_t>(bit));
    }

    mvprintw(6, 30, "GIE EEIE T0IE INTE RBIE T0IF INTF RBIF");
    for (int bit = 7; bit >= 0; --bit)
    {
        int x = 30 + (7 - bit) * 5;
        bool value = snapshot.validMemory[0x0B] ? ((snapshot.memory[0x0B] >> bit) & 1U) != 0U : false;
        addBitWidget(hitBoxes, 7, x, value, 0x0B, static_cast<uint8_t>(bit));
    }

    mvprintw(0, 75, "|  RA    7   6   5   4   3   2   1   0");
    mvprintw(1, 75, "|  TRIS");
    for (int bit = 7; bit >= 0; --bit)
    {
        int x = 84 + (7 - bit) * 4;
        bool value = snapshot.validMemory[0x85] ? ((snapshot.memory[0x85] >> bit) & 1U) != 0U : false;
        addBitWidget(hitBoxes, 1, x, value, 0x85, static_cast<uint8_t>(bit));
    }

    mvprintw(2, 75, "|  PIN ");
    for (int bit = 7; bit >= 0; --bit)
    {
        int x = 84 + (7 - bit) * 4;
        bool value = snapshot.validMemory[0x05] ? ((snapshot.memory[0x05] >> bit) & 1U) != 0U : false;
        addBitWidget(hitBoxes, 2, x, value, 0x05, static_cast<uint8_t>(bit));
    }

    mvprintw(4, 75, "|  RB    7   6   5   4   3   2   1   0");
    mvprintw(5, 75, "|  TRIS");
    for (int bit = 7; bit >= 0; --bit)
    {
        int x = 84 + (7 - bit) * 4;
        bool value = snapshot.validMemory[0x86] ? ((snapshot.memory[0x86] >> bit) & 1U) != 0U : false;
        addBitWidget(hitBoxes, 5, x, value, 0x86, static_cast<uint8_t>(bit));
    }

    mvprintw(6, 75, "|  PIN ");
    for (int bit = 7; bit >= 0; --bit)
    {
        int x = 84 + (7 - bit) * 4;
        bool value = snapshot.validMemory[0x06] ? ((snapshot.memory[0x06] >> bit) & 1U) != 0U : false;
        addBitWidget(hitBoxes, 6, x, value, 0x06, static_cast<uint8_t>(bit));
    }
}

void drawMemoryGrid(const PICSnapshot& snapshot, std::vector<HitBox>& hitBoxes)
{
    static const std::array<uint8_t, 20> rowBases = {
        0x00, 0x08, 0x10, 0x18, 0x20, 0x28, 0x30, 0x38, 0x40, 0x48,
        0x80, 0x88, 0x90, 0x98, 0xA0, 0xA8, 0xB0, 0xB8, 0xC0, 0xC8};

    mvprintw(9, 3, "00 01 02 03 04 05 06 07");
    for (int row = 0; row < static_cast<int>(rowBases.size()); ++row)
    {
        int y = 10 + row;
        uint8_t base = rowBases[row];
        mvprintw(y, 0, "%s", toHex2(base).c_str());

        for (int col = 0; col < 8; ++col)
        {
            uint8_t address = static_cast<uint8_t>(base + col);
            int x = 3 + col * 3;
            std::string cell = snapshot.validMemory[address] ? toHex2(snapshot.memory[address]) : "--";
            mvprintw(y, x, "%s", cell.c_str());
            hitBoxes.push_back(HitBox{y, x, 2, 1, HitType::MemoryCell, address, 0});
        }
    }
}

void drawAsmPanel(PIC& pic, const PICSnapshot& snapshot)
{
    int left = 32;
    int top = 9;

    mvprintw(top, left, "ASM code");

    uint16_t programLength = snapshot.programLength;
    uint16_t pc = snapshot.programCounter;

    int maxRows = 20;
    int start = 0;
    if (pc > 5)
    {
        start = static_cast<int>(pc) - 5;
    }

    for (int row = 0; row < maxRows; ++row)
    {
        int lineIndex = start + row;
        int y = top + 1 + row;

        if (lineIndex >= programLength)
        {
            mvprintw(y, left, "%-3d|", row + 1);
            continue;
        }

        std::string instructionName;
        std::string errorMessage;
        bool ok = pic.tryGetInstructionName(static_cast<uint16_t>(lineIndex), instructionName, &errorMessage);
        if (!ok)
        {
            instructionName = "<invalid>";
        }

        const char* marker = (lineIndex == pc) ? ">" : " ";
        mvprintw(y, left, "%2d%s| %-12s", row + 1, marker, instructionName.c_str());
    }
}

void drawControlPanel(const SimulationState& state, std::vector<HitBox>& hitBoxes)
{
    int x = 92;
    mvprintw(9, x, "[load file]");
    hitBoxes.push_back(HitBox{9, x, 11, 1, HitType::LoadButton, 0, 0});

    mvprintw(9, x + 13, "| Sim Controls:");
    mvprintw(11, x + 13, "Program Time:");
    mvprintw(12, x + 13, "%llu us", static_cast<unsigned long long>(state.programTimeUs.load()));

    mvprintw(14, x + 13, "[ STEP  ]");
    hitBoxes.push_back(HitBox{14, x + 13, 8, 1, HitType::StepButton, 0, 0});

    const bool running = state.runMode.load();
    mvprintw(15, x + 13, running ? "[ STOP  ]" : "[ RUN   ]");
    hitBoxes.push_back(HitBox{15, x + 13, 8, 1, HitType::RunButton, 0, 0});

    mvprintw(16, x + 13, "[ RESET ]");
    hitBoxes.push_back(HitBox{16, x + 13, 8, 1, HitType::ResetButton, 0, 0});

    mvprintw(18, x + 13, "Steps: %llu", static_cast<unsigned long long>(state.executedSteps.load()));
}

void handleLoadFile(PIC& pic, SimulationState& state)
{
    auto text = promptInput("Program path: ");
    if (!text || text->empty())
    {
        setStatus(state, "Load canceled");
        return;
    }

    try
    {
        pic.loadProgram(*text);
        {
            std::lock_guard<std::mutex> lock(state.statusMutex);
            state.loadedProgramPath = *text;
            state.statusMessage = "Loaded " + *text;
        }
    }
    catch (const std::exception& ex)
    {
        setStatus(state, std::string("Load failed: ") + ex.what());
    }
}

void handleMemoryEdit(PIC& pic, SimulationState& state, uint8_t address)
{
    auto text = promptInput("Hex value (00-FF): ");
    if (!text)
    {
        setStatus(state, "Edit canceled");
        return;
    }

    uint8_t value = 0;
    if (!parseHexByte(*text, value))
    {
        setStatus(state, "Invalid hex value");
        return;
    }

    std::string errorMessage;
    if (!pic.tryWriteRegister(address, value, &errorMessage))
    {
        setStatus(state, "Write failed: " + errorMessage);
        return;
    }

    setStatus(state, "Wrote 0x" + toHex2(value) + " to 0x" + toHex2(address));
}

void handleToggleBit(PIC& pic, SimulationState& state, uint8_t address, uint8_t bit)
{
    std::string errorMessage;
    if (!pic.tryToggleBit(address, bit, &errorMessage))
    {
        setStatus(state, "Toggle failed: " + errorMessage);
        return;
    }

    setStatus(state, "Toggled bit " + std::to_string(bit) + " at 0x" + toHex2(address));
}

void processHit(PIC& pic, SimulationState& state, const HitBox& hit)
{
    switch (hit.type)
    {
    case HitType::MemoryCell:
        handleMemoryEdit(pic, state, hit.address);
        break;
    case HitType::ToggleBit:
        handleToggleBit(pic, state, hit.address, hit.bit);
        break;
    case HitType::StepButton:
        state.runMode.store(false);
        state.stepRequested.store(true);
        setStatus(state, "Single step requested");
        break;
    case HitType::RunButton:
        state.runMode.store(!state.runMode.load());
        setStatus(state, state.runMode.load() ? "Running" : "Paused");
        break;
    case HitType::ResetButton:
        state.runMode.store(false);
        pic.reset();
        state.executedSteps.store(0);
        state.programTimeUs.store(0);
        setStatus(state, "PIC reset");
        break;
    case HitType::LoadButton:
        state.runMode.store(false);
        handleLoadFile(pic, state);
        break;
    }
}

} 

void TerminalUI::run(PIC& pic, SimulationState& state)
{
    initscr();
    cbreak();
    noecho();
    curs_set(0);
    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE);
    mousemask(ALL_MOUSE_EVENTS | REPORT_MOUSE_POSITION, nullptr);

    bool ncursesActive = true;

    while (!state.quit.load())
    {
        PICSnapshot snapshot = pic.getSnapshot();
        std::vector<HitBox> hitBoxes;

        erase();

        int maxY = 0;
        int maxX = 0;
        getmaxyx(stdscr, maxY, maxX);

        if (maxY < 33 || maxX < 130)
        {
            mvprintw(0, 0, "Terminal too small. Need at least 130x33.");
            mvprintw(1, 0, "Current: %dx%d", maxX, maxY);
        }
        else
        {
            drawTopBits(snapshot, hitBoxes);
            drawMemoryGrid(snapshot, hitBoxes);
            drawAsmPanel(pic, snapshot);
            drawControlPanel(state, hitBoxes);

            std::string loadedPath;
            {
                std::lock_guard<std::mutex> lock(state.statusMutex);
                loadedPath = state.loadedProgramPath;
            }

            if (!loadedPath.empty())
            {
                mvprintw(30, 0, "Loaded: %s", loadedPath.c_str());
            }

            mvprintw(31, 0, "Keys: q=quit r=run/stop s=step x=reset l=load file");
            mvprintw(32, 0, "Status: %s", getStatus(state).c_str());
        }

        refresh();

        int ch = getch();
        if (ch == ERR)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(1));
            continue;
        }

        if (ch == 'q' || ch == 'Q')
        {
            state.quit.store(true);
            break;
        }

        if (ch == 'r' || ch == 'R')
        {
            state.runMode.store(!state.runMode.load());
            setStatus(state, state.runMode.load() ? "Running" : "Paused");
            continue;
        }

        if (ch == 's' || ch == 'S')
        {
            state.runMode.store(false);
            state.stepRequested.store(true);
            setStatus(state, "Single step requested");
            continue;
        }

        if (ch == 'x' || ch == 'X')
        {
            state.runMode.store(false);
            pic.reset();
            state.executedSteps.store(0);
            state.programTimeUs.store(0);
            setStatus(state, "PIC reset");
            continue;
        }

        if (ch == 'l' || ch == 'L')
        {
            state.runMode.store(false);
            handleLoadFile(pic, state);
            continue;
        }

        if (ch == KEY_MOUSE)
        {
            MEVENT event;
            if (getmouse(&event) == OK)
            {
                if ((event.bstate & BUTTON1_CLICKED) || (event.bstate & BUTTON1_PRESSED))
                {
                    for (const HitBox& hit : hitBoxes)
                    {
                        if (contains(hit, event.y, event.x))
                        {
                            processHit(pic, state, hit);
                            break;
                        }
                    }
                }
            }
            continue;
        }
    }

    if (ncursesActive)
    {
        endwin();
    }
}

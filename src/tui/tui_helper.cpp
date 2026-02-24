#include "tui_helper.hpp"
#include "tui_layout.hpp"
#include <curses.h>
#include <cctype>
#include <iomanip>
#include <sstream>

bool TUI_Helper::isInAsmPanel(int y, int x)
{
    const int asmContentTop = TUI_Layout::kAsmPanelTop + 1;
    const int asmContentBottom = asmContentTop + TUI_Layout::kAsmVisibleRows - 1;
    return y >= asmContentTop && y <= asmContentBottom && x >= TUI_Layout::kAsmPanelLeft && x <= TUI_Layout::kAsmPanelRight;
        
}

int TUI_Helper::clampAsmScrollStart(int scrollStart, int totalLines)
{
    int maxStart = totalLines - TUI_Layout::kAsmVisibleRows;
    if (maxStart < 0)
    {
        maxStart = 0;
    }

    if (scrollStart < 0)
    {
        return 0;
    }
    if (scrollStart > maxStart)
    {
        return maxStart;
    }
    return scrollStart;
}

bool TUI_Helper::contains(const HitBox& hit, int y, int x)
{
    return y >= hit.y && y < hit.y + hit.height && x >= hit.x && x < hit.x + hit.width;
}

std::optional<std::string> TUI_Helper::promptInput(const std::string& prompt)
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


void TUI_Helper::setStatus(SimulationState& state, const std::string& message)
{
    std::lock_guard<std::mutex> lock(state.statusMutex);
    state.statusMessage = message;
}

bool TUI_Helper::parseHexByte(const std::string& text, uint8_t& output)
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

std::string TUI_Helper::toHex2(uint8_t value)
{
    std::ostringstream oss;
    oss << std::uppercase << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(value);
    return oss.str();
}

bool TUI_Helper::parseLstInstructionIndex(const std::string& line, uint16_t& index)
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

int TUI_Helper::findFirstCodeLineIndex(const std::vector<std::string>& fileLines)
{
    for (int i = 0; i < static_cast<int>(fileLines.size()); ++i)
    {
        uint16_t lstIndex = 0;
        if (TUI_Helper::parseLstInstructionIndex(fileLines[static_cast<size_t>(i)], lstIndex))
        {
            return i;
        }
    }
    return 0;
}

std::string TUI_Helper::getStatus(SimulationState& state)
{
    std::lock_guard<std::mutex> lock(state.statusMutex);
    return state.statusMessage;
}

short TUI_Helper::statusPairFromText(const std::string& status)
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
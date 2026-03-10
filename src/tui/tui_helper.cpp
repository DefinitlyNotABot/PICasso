#include "tui_helper.hpp"
#include "tui_layout.hpp"
#include <curses.h>
#include <cctype>
#include <iomanip>
#include <sstream>
#include <algorithm>
#include <filesystem>

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

namespace {

struct DirEntry {
    std::string name;
    bool isDirectory;
};

std::vector<DirEntry> listDirectory(const std::filesystem::path& dir)
{
    std::vector<DirEntry> entries;

    if (dir.has_parent_path() && dir.parent_path() != dir)
    {
        entries.push_back({"..", true});
    }

    std::vector<DirEntry> dirs;
    std::vector<DirEntry> files;

    std::error_code ec;
    for (const auto& entry : std::filesystem::directory_iterator(dir, ec))
    {
        if (ec)
        {
            break;
        }

        std::string filename = entry.path().filename().string();

        if (entry.is_directory(ec))
        {
            dirs.push_back({filename, true});
        }
        else if (entry.is_regular_file(ec))
        {
            std::string ext = entry.path().extension().string();
            std::string extLower = ext;
            for (char& c : extLower)
            {
                c = static_cast<char>(std::tolower(static_cast<unsigned char>(c)));
            }
            if (extLower == ".lst")
            {
                files.push_back({filename, false});
            }
        }
    }

    std::sort(dirs.begin(), dirs.end(), [](const DirEntry& a, const DirEntry& b) {
        return a.name < b.name;
    });
    std::sort(files.begin(), files.end(), [](const DirEntry& a, const DirEntry& b) {
        return a.name < b.name;
    });

    entries.insert(entries.end(), dirs.begin(), dirs.end());
    entries.insert(entries.end(), files.begin(), files.end());
    return entries;
}

} // anonymous namespace

std::optional<std::string> TUI_Helper::browseForFile(const std::filesystem::path& startDir)
{
    namespace fs = std::filesystem;

    fs::path currentDir = fs::canonical(startDir);
    int selected = 0;
    int scrollOffset = 0;

    nodelay(stdscr, FALSE);
    curs_set(0);
    keypad(stdscr, TRUE);
    mousemask(ALL_MOUSE_EVENTS | REPORT_MOUSE_POSITION, nullptr);

    for (;;)
    {
        std::vector<DirEntry> entries = listDirectory(currentDir);

        if (selected >= static_cast<int>(entries.size()))
        {
            selected = entries.empty() ? 0 : static_cast<int>(entries.size()) - 1;
        }

        int maxY = 0;
        int maxX = 0;
        getmaxyx(stdscr, maxY, maxX);

        int panelTop = 2;
        int panelHeight = maxY - 4;
        if (panelHeight < 3)
        {
            panelHeight = 3;
        }

        if (selected < scrollOffset)
        {
            scrollOffset = selected;
        }
        if (selected >= scrollOffset + panelHeight)
        {
            scrollOffset = selected - panelHeight + 1;
        }

        erase();

        attron(A_BOLD | COLOR_PAIR(CP_HEADER));
        mvprintw(0, 0, " Load .LST file ");
        attroff(A_BOLD | COLOR_PAIR(CP_HEADER));

        std::string dirStr = currentDir.string();
        if (static_cast<int>(dirStr.size()) > maxX - 1)
        {
            dirStr = "..." + dirStr.substr(dirStr.size() - static_cast<size_t>(maxX - 4));
        }
        attron(COLOR_PAIR(CP_LABEL));
        mvprintw(1, 0, "%s", dirStr.c_str());
        attroff(COLOR_PAIR(CP_LABEL));

        for (int i = 0; i < panelHeight && (scrollOffset + i) < static_cast<int>(entries.size()); ++i)
        {
            int idx = scrollOffset + i;
            const DirEntry& entry = entries[static_cast<size_t>(idx)];

            std::string display;
            if (entry.isDirectory)
            {
                display = "[" + entry.name + "/]";
            }
            else
            {
                display = " " + entry.name;
            }

            if (static_cast<int>(display.size()) > maxX - 2)
            {
                display = display.substr(0, static_cast<size_t>(maxX - 5)) + "...";
            }

            if (idx == selected)
            {
                attron(A_REVERSE | COLOR_PAIR(CP_HIGHLIGHT));
                mvprintw(panelTop + i, 1, "%-*s", maxX - 2, display.c_str());
                attroff(A_REVERSE | COLOR_PAIR(CP_HIGHLIGHT));
            }
            else if (entry.isDirectory)
            {
                attron(COLOR_PAIR(CP_VALUE));
                mvprintw(panelTop + i, 1, "%s", display.c_str());
                attroff(COLOR_PAIR(CP_VALUE));
            }
            else
            {
                mvprintw(panelTop + i, 1, "%s", display.c_str());
            }
        }

        attron(COLOR_PAIR(CP_LABEL));
        mvprintw(maxY - 1, 0, " [Enter] Select  [q/Esc] Cancel  [Up/Down] Navigate");
        attroff(COLOR_PAIR(CP_LABEL));

        refresh();

        int ch = getch();

        if (ch == 'q' || ch == 'Q' || ch == 27) // Esc
        {
            nodelay(stdscr, TRUE);
            return std::nullopt;
        }

        if (ch == KEY_UP || ch == 'k')
        {
            if (selected > 0)
            {
                --selected;
            }
        }
        else if (ch == KEY_DOWN || ch == 'j')
        {
            if (selected < static_cast<int>(entries.size()) - 1)
            {
                ++selected;
            }
        }
        else if (ch == KEY_PPAGE) // Page Up
        {
            selected -= panelHeight;
            if (selected < 0)
            {
                selected = 0;
            }
        }
        else if (ch == KEY_NPAGE) // Page Down
        {
            selected += panelHeight;
            if (selected >= static_cast<int>(entries.size()))
            {
                selected = static_cast<int>(entries.size()) - 1;
            }
            if (selected < 0)
            {
                selected = 0;
            }
        }
        else if (ch == '\n' || ch == KEY_ENTER)
        {
            if (entries.empty())
            {
                continue;
            }

            const DirEntry& entry = entries[static_cast<size_t>(selected)];

            if (entry.isDirectory)
            {
                fs::path newDir;
                if (entry.name == "..")
                {
                    newDir = currentDir.parent_path();
                }
                else
                {
                    newDir = currentDir / entry.name;
                }

                std::error_code ec;
                fs::path resolved = fs::canonical(newDir, ec);
                if (!ec)
                {
                    currentDir = resolved;
                    selected = 0;
                    scrollOffset = 0;
                }
            }
            else
            {
                std::string result = (currentDir / entry.name).string();
                nodelay(stdscr, TRUE);
                return result;
            }
        }
        else if (ch == KEY_MOUSE)
        {
            MEVENT event;
            if (getmouse(&event) == OK)
            {
                if (event.bstate & BUTTON4_PRESSED) // scroll up
                {
                    if (selected > 0)
                    {
                        --selected;
                    }
                }
                else if (event.bstate & BUTTON5_PRESSED) // scroll down
                {
                    if (selected < static_cast<int>(entries.size()) - 1)
                    {
                        ++selected;
                    }
                }
                else if ((event.bstate & BUTTON1_CLICKED) || (event.bstate & BUTTON1_PRESSED))
                {
                    int clickedIdx = scrollOffset + (event.y - panelTop);
                    if (clickedIdx >= 0 && clickedIdx < static_cast<int>(entries.size()))
                    {
                        selected = clickedIdx;
                        const DirEntry& entry = entries[static_cast<size_t>(selected)];
                        if (entry.isDirectory)
                        {
                            fs::path newDir = (entry.name == "..") ? currentDir.parent_path() : currentDir / entry.name;
                            std::error_code ec;
                            fs::path resolved = fs::canonical(newDir, ec);
                            if (!ec)
                            {
                                currentDir = resolved;
                                selected = 0;
                                scrollOffset = 0;
                            }
                        }
                        else
                        {
                            std::string result = (currentDir / entry.name).string();
                            nodelay(stdscr, TRUE);
                            return result;
                        }
                    }
                }
            }
        }
    }
}
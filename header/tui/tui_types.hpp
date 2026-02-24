#pragma once
#include <cstdint>
#include <atomic>
#include <string>
#include <vector>
#include <optional>
#include <mutex>
#include <array>


enum class HitType {
    MemoryCell,
    ToggleBit,
    StepButton,
    RunButton,
    DashButton,
    ResetButton,
    LoadButton,
    QuitButton
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

enum ColorPair : short {
    CP_HEADER = 1,
    CP_LABEL = 2,
    CP_VALUE = 3,
    CP_BUTTON = 4,
    CP_BUTTON_ACTIVE = 5,
    CP_BUTTON_DANGER = 6,
    CP_STATUS_OK = 7,
    CP_STATUS_WARN = 8,
    CP_STATUS_ERR = 9,
    CP_HIGHLIGHT = 10,
    CP_INVALID = 11,
    CP_BIT_ON = 12,
    CP_BIT_OFF = 13,
    CP_SELECTED_FIELD = 14
};

struct SimulationState {
    std::atomic<bool> quit{false};
    std::atomic<bool> runMode{false};
    std::atomic<bool> dashMode{false};
    std::atomic<bool> stepRequested{false};
    std::atomic<uint64_t> executedSteps{0};
    std::atomic<uint64_t> programTimeUs{0};

    std::mutex statusMutex;
    std::string statusMessage;
    std::string loadedProgramPath;
};

struct PICSnapshot {
    std::array<uint8_t, 256> memory{};
    std::array<bool, 256> validMemory{};
    uint8_t w = 0;
    uint8_t programCounter = 0;
    uint16_t programLength = 0;
    std::string currentInstructionName;
};
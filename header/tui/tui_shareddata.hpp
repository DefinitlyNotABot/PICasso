#pragma once
#include "tui_types.hpp"

class TUI_SharedData {
    private:
        PICSnapshot snapshot;
        std::optional<uint8_t> pendingRamEditAddress;
        int asmManualScrollStart = 0;
        bool asmManualScrollEnabled = false;
        int asmRenderedStart = 0;

        std::string shownFilePath;
        std::vector<std::string> shownFileLines;

    public:
        TUI_SharedData() = default;
        ~TUI_SharedData() = default;

        PICSnapshot& getSnapshotReference() {
            return snapshot;
        }
        std::optional<uint8_t>& getPendingRamEditAddress() {
            return pendingRamEditAddress;
        }
        void clearPendingRamEdit() {
            pendingRamEditAddress.reset();
        }
        void setPendingRamEdit(uint8_t address) {
            pendingRamEditAddress = address;
        }
        int& getAsmManualScrollStart() {
            return asmManualScrollStart;
        }
        bool& getAsmManualScrollEnabled() {
            return asmManualScrollEnabled;
        }
        int& getAsmRenderedStart() {
            return asmRenderedStart;
        }

        std::string& getShownFilePath() {
            return shownFilePath;
        }
        std::vector<std::string>& getShownFileLines() {
            return shownFileLines;
        }
};
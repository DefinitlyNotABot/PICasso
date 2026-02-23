#include "pic.hpp"
#include "logger.hpp"
#include "terminal_ui.hpp"

#include <chrono>
#include <mutex>
#include <thread>

int main()
{
    Logger::disableLogger("Compiler");
    Logger::disableLogger("PIC");
    Logger::consoleOutput = Logger::DISABLED;

    PIC pic;
    SimulationState state;
    state.loadedProgramPath = "progs/TPicSim6.LST";
    state.statusMessage = "Ready";

    pic.loadProgram(state.loadedProgramPath);

    std::thread simulationThread([&pic, &state]() {
        while (!state.quit.load()) {
            const bool runMode = state.runMode.load();
            const bool stepRequested = state.stepRequested.exchange(false);

            if (!runMode && !stepRequested) {
                std::this_thread::sleep_for(std::chrono::microseconds(200));
                continue;
            }

            std::string errorMessage;
            const bool ok = pic.tryStep(&errorMessage);
            if (!ok) {
                state.runMode.store(false);
                if (!errorMessage.empty()) {
                    std::lock_guard<std::mutex> lock(state.statusMutex);
                    state.statusMessage = "Execution halted: " + errorMessage;
                }
                std::this_thread::sleep_for(std::chrono::milliseconds(1));
                continue;
            }

            const uint64_t steps = state.executedSteps.fetch_add(1) + 1;
            state.programTimeUs.store(steps);

            if (stepRequested) {
                state.runMode.store(false);
            }

            if (runMode) {
                std::this_thread::yield();
            }
        }
    });

    TerminalUI terminalUi;
    terminalUi.run(pic, state);

    state.quit.store(true);
    if (simulationThread.joinable()) {
        simulationThread.join();
    }

    return 0;
}
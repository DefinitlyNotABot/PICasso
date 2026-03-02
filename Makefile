# Simple Makefile wrapper for CMake
BUILD_DIR := build
PROJECT   := PICasso
TEST_BIN  := AllTests
# Detect cores: nproc for Linux, sysctl for macOS
JOBS      := $(shell nproc 2>/dev/null || sysctl -n hw.ncpu 2>/dev/null || echo 1)

all:
	@mkdir -p $(BUILD_DIR)
	@cmake -S . -B $(BUILD_DIR)
	@cmake --build $(BUILD_DIR) -j $(JOBS)
	@echo "Running tests..."
	@./$(BUILD_DIR)/$(TEST_BIN)

run: all
	@./$(BUILD_DIR)/$(PROJECT)

clean:
	@rm -rf $(BUILD_DIR)

rebuild: clean all

.PHONY: all run clean rebuild
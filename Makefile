# Simple Makefile wrapper for CMake
BUILD_DIR := build
PROJECT   := PICasso
# Detect cores: nproc for Linux, sysctl for macOS
JOBS      := $(shell nproc 2>/dev/null || sysctl -n hw.ncpu 2>/dev/null || echo 1)

all:
	@mkdir -p $(BUILD_DIR)
	@cmake -S . -B $(BUILD_DIR)
	@cmake --build $(BUILD_DIR) -j $(JOBS)

run: all
	@./$(BUILD_DIR)/$(PROJECT)

clean:
	@rm -rf $(BUILD_DIR)

rebuild: clean all

test: clean
	@mkdir -p $(BUILD_DIR)
	@cmake -S . -B $(BUILD_DIR) -DBUILD_TESTING=ON
	@cmake --build $(BUILD_DIR) --target tests_runner -j $(JOBS) || true
	@cd $(BUILD_DIR) && if [ -f tests_runner ]; then ./tests_runner; else ctest --output-on-failure; fi

.PHONY: all run clean rebuild test
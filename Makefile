# Simple Makefile wrapper for CMake
BUILD_DIR := build

all:
	@mkdir -p $(BUILD_DIR)
	@cd $(BUILD_DIR) && cmake ..
	@cmake --build $(BUILD_DIR)

run: all
	@./$(BUILD_DIR)/MyProject

clean:
	@rm -rf $(BUILD_DIR)

rebuild: clean all

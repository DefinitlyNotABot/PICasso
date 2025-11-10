# Simple Makefile wrapper for CMake
BUILD_DIR := build
PROJECT := PICasso

all:
	@mkdir -p $(BUILD_DIR)
	@cd $(BUILD_DIR) && cmake ..
	@cmake --build $(BUILD_DIR)

run: all
	@./$(BUILD_DIR)/$(PROJECT)

clean:
	@rm -rf $(BUILD_DIR)

rebuild: clean all

test:
	make clean
	make
	@mkdir -p $(BUILD_DIR)
	@cd $(BUILD_DIR) && cmake -DBUILD_TESTING=ON ..
	@cmake --build $(BUILD_DIR) --target tests_runner || true
	@cd $(BUILD_DIR) && if [ -f tests_runner ]; then ./tests_runner; else ctest --output-on-failure; fi

.PHONY: all run clean rebuild tests

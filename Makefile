#!/bin/bash

BUILD_TYPE=${1:-Release}
CMAKE_SOURCE_DIR = $(shell pwd)
CMAKE_BUILD_DIR = $(CMAKE_SOURCE_DIR)/build
CMAKE_COVERAGE_DIR = $(CMAKE_BUILD_DIR)/coverage

SRC_DIR = $(CMAKE_SOURCE_DIR)/src
INCLUDE_DIR = $(CMAKE_SOURCE_DIR)/include
TESTS_DIR = $(CMAKE_SOURCE_DIR)/tests

.PHONY: build clean run run-tests format cppcheck coverage

build:
	@echo "Creating build folder"
	@mkdir -p $(CMAKE_BUILD_DIR)
	@mkdir -p $(CMAKE_COVERAGE_DIR)
	@echo "Running CMake with build type: $(BUILD_TYPE)"
	@cd $(CMAKE_BUILD_DIR) && cmake -DCMAKE_BUILD_TYPE=$(BUILD_TYPE) $(CMAKE_SOURCE_DIR)
	@echo "Building project"
	@cd $(CMAKE_BUILD_DIR) && make

debug:
	@make build BUILD_TYPE=Debug

release:
	@make build BUILD_TYPE=Release

coverage: clean
	@echo "Building project with coverage flags"
	@make build BUILD_TYPE=Coverage
	@echo "Running tests for coverage"
	@make test
	@echo "Generating coverage report using gcov"
	@find $(CMAKE_BUILD_DIR) -name "*.gcno" -exec gcov {} \;
	@echo "Moving coverage reports to $(CMAKE_COVERAGE_DIR)"
	@find . -name "*.gcov" -exec mv {} $(CMAKE_COVERAGE_DIR) \;
	@echo "Coverage report generated in $(CMAKE_COVERAGE_DIR)"

clean:
	@echo "Cleaning build directory..."
	@rm -rf $(CMAKE_BUILD_DIR)
	@echo "Build directory cleaned"

run:
	@./$(CMAKE_BUILD_DIR)/src/Main

test:
	@cd $(CMAKE_BUILD_DIR) && ctest --output-on-failure

format:
	@echo "Formating files"
	@find $(SRC_DIR) $(TESTS_DIR) -name "CMakeLists.txt" -exec cmake-format -i {} \;

cppcheck:
	@cppcheck --enable=all -Iinclude --error-exitcode=1 --suppress=missingIncludeSystem --inconclusive src/
# @cppcheck --enable=all -Iinclude -I/usr/include -I/usr/include/CppUTest --error-exitcode=1 --suppress=missingIncludeSystem --suppress=*:*/usr/include/CppUTest/* --inconclusive tests/

tidy:
	@clang-tidy -p=build -extra-arg=-Iinclude src/*.cpp include/*.hpp tests/*.cpp -- -std=c++20

#!/bin/bash

BUILD_TYPE=${1:-Release}
CMAKE_SOURCE_DIR=$(shell pwd)
CMAKE_BUILD_DIR=${CMAKE_SOURCE_DIR}/build
CMAKE_COVERAGE_DIR=${CMAKE_BUILD_DIR}/coverage

SRC_DIR=${CMAKE_SOURCE_DIR}/src
TESTS_DIR=${CMAKE_SOURCE_DIR}/tests

SRC_FILES=$(shell find ${SRC_DIR} ${TESTS_DIR} -name "*.cpp" -o -name "*.hpp")
INCLUDE_PATHS=$(shell find ${SRC_DIR} -type d -exec echo -I{} \; | tr '\n' ' ')
EXTRA_ARG=$(shell find ${SRC_DIR}/ -type d -exec echo --extra-arg=-I{}/ \; | tr '\n' ' ')

.PHONY: all build clean run test format cppcheck coverage tidy

# Default target
all: build

# Build the project
build:
	@echo "Creating build folder"
	@mkdir -p ${CMAKE_BUILD_DIR}
	@mkdir -p ${CMAKE_COVERAGE_DIR}
	@echo "Running CMake with build type: ${BUILD_TYPE}"
	@cd ${CMAKE_BUILD_DIR} && cmake -DCMAKE_BUILD_TYPE=${BUILD_TYPE} ${CMAKE_SOURCE_DIR} || { echo 'CMake failed'; exit 1; }
	@echo "Building project"
	@cd ${CMAKE_BUILD_DIR} && make || { echo 'Build failed'; exit 1; }

# Debug and release builds
debug:
	@$(MAKE) build BUILD_TYPE=Debug

release:
	@$(MAKE) build BUILD_TYPE=Release

# Coverage build and reporting
coverage: clean
	@echo "Building project with coverage flags"
	@$(MAKE) build BUILD_TYPE=Coverage
	@echo "Running tests for coverage"
	@$(MAKE) test
	@echo "Generating coverage report using gcov"
	@find ${CMAKE_BUILD_DIR} -name "*.gcno" -exec gcov {} \; || { echo 'gcov failed'; exit 1; }
	@echo "Moving coverage reports to ${CMAKE_COVERAGE_DIR}"
	@find . -name "*.gcov" -exec mv {} ${CMAKE_COVERAGE_DIR} \;
	@echo "Coverage report generated in ${CMAKE_COVERAGE_DIR}"

# Clean build directory
clean:
	@echo "Cleaning build directory..."
	@rm -rf ${CMAKE_BUILD_DIR}
	@echo "Build directory cleaned"

# Run the project
run:
	@${CMAKE_BUILD_DIR}/src/Main || { echo 'Run failed'; exit 1; }

# Run tests
test:
	@if [ -n "$(TESTNAME)" ]; then \
		TEST_PATH=$(shell find ${CMAKE_BUILD_DIR}/tests -name $(TESTNAME)); \
		if [ -z "$$TEST_PATH" ]; then \
			echo "Test executable $(TESTNAME) not found"; \
			exit 1; \
		fi; \
		$$TEST_PATH -v || { echo 'Tests failed'; exit 1; }; \
	else \
		cd ${CMAKE_BUILD_DIR} && ctest --output-on-failure --verbose || { echo 'Tests failed'; exit 1; }; \
	fi

# Format CMake files
format:
	@echo "Formatting files"
	@find ${SRC_DIR} ${TESTS_DIR} -name "CMakeLists.txt" -exec cmake-format -i {} \;

# Run cppcheck with error checking
cppcheck:
	@cppcheck --enable=all ${INCLUDE_PATHS} --error-exitcode=1 --suppress=missingIncludeSystem --inconclusive ${SRC_FILES} || { echo 'cppcheck failed'; exit 1; }

# Run clang-tidy
tidy:
	@echo "Running clang-tidy..."

	@if [ -n "$(FILE)" ]; then \
		FILES=`find ${SRC_DIR} ${TESTS_DIR} -name "$(FILE)"`; \
	else \
		FILES="${SRC_FILES}"; \
	fi; \
	echo $$FILES; \
	for file in $$FILES; do \
		echo "Checking $$file..."; \
		clang-tidy -p build/ ${EXTRA_ARG} $$file || { echo 'clang-tidy failed on $$file'; exit 1; }; \
	done

# Set default variables
BUILD_TYPE ?= Release
BUILD_SCT ?= OFF

CMAKE_SOURCE_DIR := $(CURDIR)
CMAKE_BUILD_DIR := $(CMAKE_SOURCE_DIR)/build
CMAKE_COVERAGE_DIR := $(CMAKE_BUILD_DIR)/coverage

SRC_DIR := $(CMAKE_SOURCE_DIR)/src
TESTS_DIR := $(CMAKE_SOURCE_DIR)/tests/ut
SCT_DIR := $(CMAKE_SOURCE_DIR)/tests/sct

SRC_FILES := $(shell find $(SRC_DIR) $(TESTS_DIR) -name "*.cpp" -o -name "*.hpp")
EXTRA_ARG := $(shell find $(SRC_DIR) -type d -exec echo --extra-arg=-I{} \; | tr '\n' ' ')

SCT_FILES := $(shell find $(SCT_DIR) -name "*.cpp" -o -name "*.hpp")
EXTRA_ARG_SCT := $(shell find $(SCT_DIR) -type d -exec echo --extra-arg=-I{} \; | tr '\n' ' ')

.PHONY: all build clean run test format cppcheck coverage tidy

# Default target
all: build

# Build the project
build:
	@echo "Creating build folder"
	@mkdir -p $(CMAKE_BUILD_DIR)
	@mkdir -p $(CMAKE_COVERAGE_DIR)
	@echo "Running CMake with build type: $(BUILD_TYPE)"
	@cd $(CMAKE_BUILD_DIR) && cmake -DCMAKE_BUILD_TYPE=$(BUILD_TYPE) -DBUILD_SCT=$(BUILD_SCT) $(CMAKE_SOURCE_DIR) || { echo 'CMake failed'; exit 1; }
	@echo "Building project"
	@cd $(CMAKE_BUILD_DIR) && $(MAKE) -j4 || { echo 'Build failed'; exit 1; }

build-sct: BUILD_SCT=ON
build-sct: build

# Debug and release builds
debug: BUILD_TYPE=Debug
debug: build

debug-sct: BUILD_SCT=ON
debug-sct: debug

release: BUILD_TYPE=Release
release: build

# Coverage build and reporting
coverage: clean
	@echo "Build  ing project with coverage flags"
	@$(MAKE) build BUILD_TYPE=Coverage
	@echo "Running tests for coverage"
	@$(MAKE) test
	@echo "Capturing initial coverage"
	@lcov --capture --directory $(CMAKE_BUILD_DIR) --output-file $(CMAKE_COVERAGE_DIR)/coverage.info
	@echo "Filtering out system, external library files, and unit tests"
	@lcov --remove $(CMAKE_COVERAGE_DIR)/coverage.info '/usr/*' '*/external/*' '*/tests/*' --output-file $(CMAKE_COVERAGE_DIR)/coverage_filtered.info
	@echo "Generating coverage report"
	@genhtml $(CMAKE_COVERAGE_DIR)/coverage_filtered.info --output-directory $(CMAKE_COVERAGE_DIR)/report
	@echo "Coverage report generated in $(CMAKE_COVERAGE_DIR)/report"

coverage-sct: BUILD_SCT=ON
coverage-sct: coverage

# Clean build directory
clean:
	@echo "Cleaning build directory..."
	@rm -rf $(CMAKE_BUILD_DIR)
	@echo "Build directory cleaned"

# Run the project
run:
	@$(CMAKE_BUILD_DIR)/src/Main || { echo 'Run failed'; exit 1; }

# Run tests
test:
	@if [ -n "$(FILE)" ]; then \
		TEST_PATH=$$(find $(CMAKE_BUILD_DIR)/tests/ -name $(FILE)); \
		if [ -z "$$TEST_PATH" ]; then \
			echo "Test executable $(FILE) not found"; \
			exit 1; \
		fi; \
		$$TEST_PATH -v || { echo 'Tests failed'; exit 1; }; \
	else \
		cd $(CMAKE_BUILD_DIR) && ctest --output-on-failure --verbose || { echo 'Tests failed'; exit 1; }; \
	fi

# Format CMake files
format:
	@echo "Formatting files"
	@find $(SRC_DIR) $(TESTS_DIR) $(SCT_DIR) -name "CMakeLists.txt" -exec cmake-format -i {} \;

# Run cppcheck with error checking
cppcheck:
	@cppcheck --project=${CMAKE_BUILD_DIR}/compile_commands.json --enable=all --error-exitcode=1 --suppress=missingInclude --suppress=missingIncludeSystem --suppress=checkersReport || { echo 'cppcheck failed'; exit 1; }

# Run clang-tidy
tidy:
	@echo "Running clang-tidy..."
	@if [ -n "$(FILE)" ]; then \
		FILES=$$(find $(SRC_DIR) $(TESTS_DIR) $(SCT_DIR) -name "$(FILE)"); \
	else \
		FILES="$(SRC_FILES)"; \
	fi; \
	for file in $$FILES; do \
		echo "Checking $$file..."; \
		clang-tidy -p $(CMAKE_BUILD_DIR) $(EXTRA_ARG) $$file || { echo 'clang-tidy failed on $$file'; exit 1; }; \
	done

tidy-sct:
	@echo "Running clang-tidy on SCT..."
	@for file in $(SCT_FILES); do \
		echo "Checking $$file..."; \
		clang-tidy -p $(CMAKE_BUILD_DIR) $(EXTRA_ARG_SCT) $$file || { echo 'clang-tidy failed on $$file'; exit 1; }; \
	done

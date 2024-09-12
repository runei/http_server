CMAKE_BUILD_DIR = build
CMAKE_SOURCE_DIR = $(shell pwd)

.PHONY: build clean run run-tests format cppcheck

build:
	@echo "Creating build folder"
	@mkdir -p $(CMAKE_BUILD_DIR)
	@echo "Running CMake"
	@cd $(CMAKE_BUILD_DIR) && cmake $(CMAKE_SOURCE_DIR)
	@echo "Building project"
	@cd $(CMAKE_BUILD_DIR) && make

clean:
	@echo "Cleaning build directory..."
	@rm -rf $(CMAKE_BUILD_DIR)
	@echo "Build directory cleaned"

run:
	@./$(CMAKE_BUILD_DIR)/src/Main

run-tests:
	@cd $(CMAKE_BUILD_DIR) && ctest --output-on-failure

format:
	@echo "Formating files"
	@find src tests -name "CMakeLists.txt" -exec cmake-format -i {} \;

cppcheck:
	@cppcheck --enable=all -Iinclude --error-exitcode=1 --suppress=missingIncludeSystem --inconclusive src/
# @cppcheck --enable=all -Iinclude -I/usr/include -I/usr/include/CppUTest --error-exitcode=1 --suppress=missingIncludeSystem --suppress=*:*/usr/include/CppUTest/* --inconclusive tests/

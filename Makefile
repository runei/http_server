CMAKE_BUILD_DIR = build
CMAKE_SOURCE_DIR = $(shell pwd)

.PHONY: all build clean

#Create the build folder, run CMake, and build the project
build:
	@echo "Creating build folder"
	@mkdir -p $(CMAKE_BUILD_DIR)
	@echo "Running CMake"
	@cd $(CMAKE_BUILD_DIR) && cmake $(CMAKE_SOURCE_DIR)
	@echo "Building project"
	@cd $(CMAKE_BUILD_DIR) && make

# Clean the build folder
clean:
	@echo "Cleaning build directory..."
	@rm -rf $(CMAKE_BUILD_DIR)
	@echo "Build directory cleaned"

format:
	@echo "Formating files"
	@find src tests -name "CMakeLists.txt" -exec cmake-format -i {} \;

cppcheck:
	@cppcheck --enable=all -Iinclude --error-exitcode=1 --suppress=missingIncludeSystem --inconclusive src/
#	@cppcheck --enable=all -Iinclude -I/usr/include -I/usr/include/CppUTest --suppress=*:*/usr/include/CppUTest/* --error-exitcode=1 --suppress=missingIncludeSystem --inconclusive src/ tests/

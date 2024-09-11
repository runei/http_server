add_library(
    Calculator
    STATIC
    Calculator.cpp
)

target_include_directories(Calculator PUBLIC ${CMAKE_SOURCE_DIR}/include)

add_executable(Main main.cpp)

target_link_libraries(Main PRIVATE Calculator)

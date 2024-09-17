add_library(
    SocketManager
    STATIC
    SocketManager.cpp
)

target_include_directories(SocketManager PUBLIC ${CMAKE_SOURCE_DIR}/include)

add_executable(Main main.cpp)

target_link_libraries(Main PRIVATE SocketManager)

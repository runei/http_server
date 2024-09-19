add_library(
    SocketManager
    STATIC
    SocketManager.cpp
)

target_include_directories(SocketManager PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

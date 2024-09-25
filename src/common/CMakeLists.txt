# SockerException
add_library(
    SocketException
    INTERFACE
)

target_include_directories(
    SocketException INTERFACE $(CMAKE_CURRENT_SOURCE_DIR)
)

# Definitions
add_library(
    Definitions
    INTERFACE
)

target_include_directories(
    Definitions INTERFACE $(CMAKE_CURRENT_SOURCE_DIR)
)

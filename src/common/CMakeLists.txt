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

target_include_directories(Definitions INTERFACE $(CMAKE_CURRENT_SOURCE_DIR))

# Result
add_library(
    Result
    INTERFACE
)

target_include_directories(Result INTERFACE $(CMAKE_CURRENT_SOURCE_DIR))

target_link_libraries(
    Result
    INTERFACE SocketException
              HttpStatusCode
)

# CommonFunctions
add_library(
    CommonFunctions
    INTERFACE
)

target_include_directories(
    CommonFunctions INTERFACE $(CMAKE_CURRENT_SOURCE_DIR)
)

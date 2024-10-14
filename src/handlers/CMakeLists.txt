# ErrorHandler
add_library(
    ErrorHandler
    STATIC
    ErrorHandler.cpp
)

target_include_directories(ErrorHandler PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(
    ErrorHandler
    PUBLIC HttpStatusCode
           HttpResponse
)

# FileRequestHandler
add_library(
    FileRequestHandler
    STATIC
    FileRequestHandler.cpp
)

target_include_directories(
    FileRequestHandler PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(
    FileRequestHandler
    PUBLIC HttpStatusCode
           HttpResponse
           CommonFunctions
           ErrorHandler
)

# IRequestHandler
add_library(
    IRequestHandler
    INTERFACE
)

target_include_directories(
    IRequestHandler INTERFACE $(CMAKE_CURRENT_SOURCE_DIR)
)

target_link_libraries(
    IRequestHandler
    INTERFACE HttpResponse
              HttpRequest
)

# RequestDispatcher
add_library(
    RequestDispatcher
    STATIC
    RequestDispatcher.cpp
)

target_include_directories(RequestDispatcher PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(
    RequestDispatcher
    PUBLIC RequestParser
           IRequestHandler
           ErrorHandler
)

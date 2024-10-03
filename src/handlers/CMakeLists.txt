# ErrorHandler
add_library(
    ErrorHandler
    STATIC
    ErrorHandler.cpp
)

target_include_directories(ErrorHandler PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(ErrorHandler PUBLIC HttpStatusCode HttpResponse)

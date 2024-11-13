# TestCase
add_library(
    TestCase
    STATIC
    TestCase.cpp
)

target_include_directories(TestCase PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(
    TestCase
    PUBLIC TestCaseResult
           Definitions
           Logger
)

# ServerTestCase add_library( ServerTestCase STATIC ServerTestCase.cpp )

# target_include_directories(ServerTestCase PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# target_link_libraries( ServerTestCase PUBLIC Server TestCase Logger )

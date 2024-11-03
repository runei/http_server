#include <CppUTest/TestHarness.h> // NOLINT(misc-include-cleaner)

#include <CppUTest/UtestMacros.h>

#include <cerrno>
#include <cstring>
#include <string_view>

#include "SocketException.hpp"

TEST_GROUP (SocketExceptionTest)
{
    void setup() override {}
    void teardown() override {}
};

TEST (SocketExceptionTest, ThrowErrorMessage)
{
    // Arrange
    const std::string_view expected = "Connection failed";

    // Act
    const SocketException actual("Connection failed");

    // Assert
    STRCMP_EQUAL(expected.data(), actual.what());
}

TEST (SocketExceptionTest, ErrorNumberInMessage)
{
    // Arrange
    const int              error_number = EACCES; // Permission denied error code
    const std::string_view expected     = "Connection failed: Permission denied";

    // Act
    const SocketException actual("Connection failed", error_number);

    // Assert
    STRCMP_EQUAL(expected.data(), actual.what());
}

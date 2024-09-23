#include <CppUTest/TestHarness.h>

#include <cstring>

#include "SocketException.hpp"

TEST_GROUP (SocketExceptionTest)
{
    void setup() override {}
    void teardown() override {}
};

TEST (SocketExceptionTest, ThrowErrorMessage)
{
    // Arrange
    std::string_view expected = "Connection failed";

    // Act
    SocketException actual("Connection failed");

    // Assert
    STRCMP_EQUAL(expected.data(), actual.what());
}

TEST (SocketExceptionTest, ErrorNumberInMessage)
{
    // Arrange
    int              error_number = EACCES; // Permission denied error code
    std::string_view expected     = "Connection failed: Permission denied";

    // Act
    SocketException actual("Connection failed", error_number);

    // Assert
    STRCMP_EQUAL(expected.data(), actual.what());
}

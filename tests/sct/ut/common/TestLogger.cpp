#include <CppUTest/TestHarness.h> // NOLINT(misc-include-cleaner)

#include <CppUTest/UtestMacros.h>

#include <cstddef>
#include <memory>
#include <string>
#include <vector>

#include "Logger.hpp"

class MockLogger : public Logger
{
public:
    size_t      getNumberMessages() const { return m_mock_file.size(); }
    std::string getMessage(size_t index) const { return m_mock_file[index]; }

protected:
    void writeToFile(const std::string& message) override { m_mock_file.push_back(message); }

private:
    std::vector<std::string> m_mock_file;
};

TEST_GROUP (LoggerTest)
{
    void setup() override
    {
        m_logger = std::make_unique<MockLogger>();
    }

    std::unique_ptr<MockLogger>& getLogger()
    {
        return m_logger;
    };

private:
    std::unique_ptr<MockLogger> m_logger;
};

TEST (LoggerTest, LogInfoMessage)
{
    // Arrange
    const std::string message  = "This is an info message.";
    const std::string expected = "[INFO] This is an info message.";

    // Act
    getLogger()->logInfo(message);

    // Assert
    CHECK_EQUAL(1, getLogger()->getNumberMessages());
    STRCMP_EQUAL(expected.data(), getLogger()->getMessage(0).data());
}

TEST (LoggerTest, LogSuccessMessage)
{
    // Arrange
    const std::string message  = "This is an success message.";
    const std::string expected = "[SUCCESS] This is an success message.";

    // Act
    getLogger()->logSuccess(message);

    // Assert
    CHECK_EQUAL(1, getLogger()->getNumberMessages());
    STRCMP_EQUAL(expected.data(), getLogger()->getMessage(0).data());
}

TEST (LoggerTest, LogErrorMessage)
{
    // Arrange
    const std::string message  = "This is an error message.";
    const std::string expected = "[ERROR] This is an error message.";

    // Act
    getLogger()->logError(message);

    // Assert
    CHECK_EQUAL(1, getLogger()->getNumberMessages());
    STRCMP_EQUAL(expected.data(), getLogger()->getMessage(0).data());
}

#include <CppUTest/TestHarness.h> // NOLINT(misc-include-cleaner)

#include <CppUTest/UtestMacros.h>

#include <memory>
#include <string>
#include <string_view>

#include "Logger.hpp"
#include "Result.hpp"

TEST_GROUP (ResultTest)
{
    void setup() override
    {
        Logger::getInstance().disableFileOutput();
        m_result = std::make_unique<Result>();
    }

    std::unique_ptr<Result>& getResult()
    {
        return m_result;
    }

private:
    std::unique_ptr<Result> m_result;
};

TEST (ResultTest, LogSinglePassTest)
{
    // Arrange
    const std::string test_name     = "SinglePassTest";
    const std::string test_message  = "Executed successfully";
    const double      test_duration = 50.0;

    // Act
    getResult()->logResult(test_name, true, test_message, test_duration);

    // Assert
    STRCMP_CONTAINS("PASS", getResult()->getResults().c_str());
    STRCMP_CONTAINS(test_name.c_str(), getResult()->getResults().c_str());
    STRCMP_CONTAINS(test_message.c_str(), getResult()->getResults().c_str());
}

TEST (ResultTest, LogSingleFailTest)
{
    // Arrange
    const std::string test_name     = "SingleFailTest";
    const std::string test_message  = "Execution failed";
    const double      test_duration = 30.0;

    // Act
    getResult()->logResult(test_name, false, test_message, test_duration);

    // Assert
    STRCMP_CONTAINS("FAIL", getResult()->getResults().c_str());
    STRCMP_CONTAINS(test_name.c_str(), getResult()->getResults().c_str());
    STRCMP_CONTAINS(test_message.c_str(), getResult()->getResults().c_str());
}

TEST (ResultTest, ClearResults)
{
    // Arrange
    const std::string_view expected =
        "Test Name           Result    Message                                           Duration "
        "(ms)\n--------------------------------------------------------------------------------\n";
    const double duration1 = 10.0;
    const double duration2 = 15.0;

    getResult()->logResult("Test1", true, "Success message", duration1);
    getResult()->logResult("Test2", false, "Failure message", duration2);

    // Act
    getResult()->clearResults();

    // Assert
    STRCMP_EQUAL(expected.data(), getResult()->getResults().c_str());
}

// Test multiple results
TEST (ResultTest, LogMultipleResults)
{
    // Arrange
    const std::string test_name1    = "MultiTest1";
    const std::string test_message1 = "First test";
    const double      duration1     = 20.0;

    const std::string test_name2    = "MultiTest2";
    const std::string test_message2 = "Second test";
    const double      duration2     = 25.0;

    // Act
    getResult()->logResult(test_name1, true, test_message1, duration1);
    getResult()->logResult(test_name2, false, test_message2, duration2);

    // Assert
    STRCMP_CONTAINS("PASS", getResult()->getResults().c_str());
    STRCMP_CONTAINS("FAIL", getResult()->getResults().c_str());
    STRCMP_CONTAINS(test_name1.c_str(), getResult()->getResults().c_str());
    STRCMP_CONTAINS(test_name2.c_str(), getResult()->getResults().c_str());
    STRCMP_CONTAINS(test_message1.c_str(), getResult()->getResults().c_str());
    STRCMP_CONTAINS(test_message2.c_str(), getResult()->getResults().c_str());
}

TEST (ResultTest, LogResultIncludesDuration)
{
    // Arrange
    const std::string test_name     = "DurationTest";
    const std::string test_message  = "Timing test";
    const double      test_duration = 100.0;

    // Act
    getResult()->logResult(test_name, true, test_message, test_duration);

    // Assert
    STRCMP_CONTAINS("100.0", getResult()->getResults().c_str());
}

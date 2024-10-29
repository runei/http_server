#include "CppUTest/TestHarness.h"

#include <memory>

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
    const std::string TestName     = "SinglePassTest";
    const std::string TestMessage  = "Executed successfully";
    const double      TestDuration = 50.0;

    // Act
    getResult()->logResult(TestName, true, TestMessage, TestDuration);

    // Assert
    STRCMP_CONTAINS("PASS", getResult()->getResults().c_str());
    STRCMP_CONTAINS(TestName.c_str(), getResult()->getResults().c_str());
    STRCMP_CONTAINS(TestMessage.c_str(), getResult()->getResults().c_str());
}

TEST (ResultTest, LogSingleFailTest)
{
    // Arrange
    const std::string TestName     = "SingleFailTest";
    const std::string TestMessage  = "Execution failed";
    const double      TestDuration = 30.0;

    // Act
    getResult()->logResult(TestName, false, TestMessage, TestDuration);

    // Assert
    STRCMP_CONTAINS("FAIL", getResult()->getResults().c_str());
    STRCMP_CONTAINS(TestName.c_str(), getResult()->getResults().c_str());
    STRCMP_CONTAINS(TestMessage.c_str(), getResult()->getResults().c_str());
}

TEST (ResultTest, ClearResults)
{
    // Arrange
    std::string_view expected =
        "Test Name           Result    Message                                           Duration "
        "(ms)\n--------------------------------------------------------------------------------\n";
    const double Duration1 = 10.0;
    const double Duration2 = 15.0;

    getResult()->logResult("Test1", true, "Success message", Duration1);
    getResult()->logResult("Test2", false, "Failure message", Duration2);

    // Act
    getResult()->clearResults();

    // Assert
    STRCMP_EQUAL(expected.data(), getResult()->getResults().c_str());
}

// Test multiple results
TEST (ResultTest, LogMultipleResults)
{
    // Arrange
    const std::string TestName1    = "MultiTest1";
    const std::string TestMessage1 = "First test";
    const double      Duration1    = 20.0;

    const std::string TestName2    = "MultiTest2";
    const std::string TestMessage2 = "Second test";
    const double      Duration2    = 25.0;

    // Act
    getResult()->logResult(TestName1, true, TestMessage1, Duration1);
    getResult()->logResult(TestName2, false, TestMessage2, Duration2);

    // Assert
    STRCMP_CONTAINS("PASS", getResult()->getResults().c_str());
    STRCMP_CONTAINS("FAIL", getResult()->getResults().c_str());
    STRCMP_CONTAINS(TestName1.c_str(), getResult()->getResults().c_str());
    STRCMP_CONTAINS(TestName2.c_str(), getResult()->getResults().c_str());
    STRCMP_CONTAINS(TestMessage1.c_str(), getResult()->getResults().c_str());
    STRCMP_CONTAINS(TestMessage2.c_str(), getResult()->getResults().c_str());
}

TEST (ResultTest, LogResultIncludesDuration)
{
    // Arrange
    const std::string TestName     = "DurationTest";
    const std::string TestMessage  = "Timing test";
    const double      TestDuration = 100.0;

    // Act
    getResult()->logResult(TestName, true, TestMessage, TestDuration);

    // Assert
    STRCMP_CONTAINS("100.0", getResult()->getResults().c_str());
}

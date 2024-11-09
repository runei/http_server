#include <CppUTest/TestHarness.h> // NOLINT(misc-include-cleaner)

#include <CppUTest/UtestMacros.h>

#include <memory>
#include <utility>

#include "Logger.hpp"
#include "MockTestCase.hpp"
#include "TestSuite.hpp"

TEST_GROUP (TestSuiteTest)
{
    void setup() override
    {
        m_suite = std::make_unique<TestSuite>();
        Logger::getInstance().disableFileOutput();
    }

    std::unique_ptr<TestSuite>& getTestSuite()
    {
        return m_suite;
    }

private:
    std::unique_ptr<TestSuite> m_suite;
};

TEST (TestSuiteTest, AddTest_ValidTestCase)
{
    // Arrange
    auto test_case = std::make_unique<MockTestCase>();

    // Act
    getTestSuite()->addTest(std::move(test_case));

    // Assert
    getTestSuite()->runAllTests();
    const auto& results = getTestSuite()->getResults();
    CHECK_EQUAL(1, results.size());
}

TEST (TestSuiteTest, RunAllTests_AllTestsPass)
{
    // Arrange
    auto test1 = std::make_unique<MockTestCase>();
    auto test2 = std::make_unique<MockTestCase>();

    getTestSuite()->addTest(std::move(test1));
    getTestSuite()->addTest(std::move(test2));

    // Act
    getTestSuite()->runAllTests();

    // Assert
    const auto& results = getTestSuite()->getResults();
    CHECK_EQUAL(2, results.size());
    CHECK_TRUE(results[0].isSuccess());
    CHECK_TRUE(results[1].isSuccess());
}

TEST (TestSuiteTest, RunAllTests_TestFails)
{
    // Arrange
    auto test1 = std::make_unique<MockTestCase>();
    auto test2 = std::make_unique<MockTestCase>();
    test2->setExecuteResult(false, "Execution failed");

    getTestSuite()->addTest(std::move(test1));
    getTestSuite()->addTest(std::move(test2));

    // Act
    getTestSuite()->runAllTests();

    // Assert
    const auto& results = getTestSuite()->getResults();
    CHECK_EQUAL(2, results.size());
    CHECK_TRUE(results[0].isSuccess());
    CHECK_FALSE(results[1].isSuccess());
    STRCMP_EQUAL("Execution Failed: Execution failed", results[1].getMessage().c_str());
}

TEST (TestSuiteTest, GetResults_BeforeRunning_ShouldReturnEmptyVector)
{
    // Arrange & Act
    const auto& results = getTestSuite()->getResults();

    // Assert
    CHECK_TRUE(results.empty());
}

TEST (TestSuiteTest, RunAllTests_MultipleMixedResults_ShouldCollectAllResults)
{
    // Arrange
    auto test1 = std::make_unique<MockTestCase>();
    auto test2 = std::make_unique<MockTestCase>();
    auto test3 = std::make_unique<MockTestCase>();

    test1->setExecuteResult(true, "");
    test2->setExecuteResult(false, "Execution failed");
    test3->setExecuteResult(true, "");

    getTestSuite()->addTest(std::move(test1));
    getTestSuite()->addTest(std::move(test2));
    getTestSuite()->addTest(std::move(test3));

    // Act
    getTestSuite()->runAllTests();

    // Assert
    const auto& results = getTestSuite()->getResults();
    CHECK_EQUAL(3, results.size());
    CHECK_TRUE(results[0].isSuccess());
    CHECK_FALSE(results[1].isSuccess());
    CHECK_TRUE(results[2].isSuccess());
}

TEST (TestSuiteTest, RunAllTests_NoTestsAdded_ShouldDoNothing)
{
    // Arrange
    // No tests added to the suite

    // Act
    getTestSuite()->runAllTests();

    // Assert
    const auto& results = getTestSuite()->getResults();
    CHECK_EQUAL(0, results.size());
}

TEST (TestSuiteTest, AddTest_MultipleValidTestCases)
{
    // Arrange
    auto test1 = std::make_unique<MockTestCase>();
    auto test2 = std::make_unique<MockTestCase>();
    auto test3 = std::make_unique<MockTestCase>();

    // Act
    getTestSuite()->addTest(std::move(test1));
    getTestSuite()->addTest(std::move(test2));
    getTestSuite()->addTest(std::move(test3));

    // Assert
    getTestSuite()->runAllTests();
    const auto& results = getTestSuite()->getResults();
    CHECK_EQUAL(3, results.size());
}

TEST (TestSuiteTest, RunAllTests_TestsWithTeardownFailure)
{
    // Arrange
    auto test1 = std::make_unique<MockTestCase>();
    test1->setTeardownResult(false, "Teardown failed");

    getTestSuite()->addTest(std::move(test1));

    // Act
    getTestSuite()->runAllTests();

    // Assert
    const auto& results = getTestSuite()->getResults();
    CHECK_EQUAL(1, results.size());
    CHECK_TRUE(results[0].isSuccess());
}

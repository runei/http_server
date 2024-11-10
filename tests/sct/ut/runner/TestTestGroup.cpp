#include <CppUTest/TestHarness.h> // NOLINT(misc-include-cleaner)

#include <CppUTest/UtestMacros.h>

#include <memory>
#include <utility>

#include "Logger.hpp"
#include "MockTestCase.hpp"
#include "TestGroup.hpp"

TEST_GROUP (TestGroupTest)
{
    void setup() override
    {
        m_suite = std::make_unique<TestGroup>();
        Logger::getInstance().disableFileOutput();
    }

    std::unique_ptr<TestGroup>& getTestGroup()
    {
        return m_suite;
    }

private:
    std::unique_ptr<TestGroup> m_suite;
};

TEST (TestGroupTest, AddTest_ValidTestCase)
{
    // Arrange
    auto test_case = std::make_unique<MockTestCase>();

    // Act
    getTestGroup()->addTest(std::move(test_case));

    // Assert
    getTestGroup()->runAllTests();
    const auto& results = getTestGroup()->getResults();
    CHECK_EQUAL(1, results.size());
}

TEST (TestGroupTest, RunAllTests_AllTestsPass)
{
    // Arrange
    auto test1 = std::make_unique<MockTestCase>();
    auto test2 = std::make_unique<MockTestCase>();

    getTestGroup()->addTest(std::move(test1));
    getTestGroup()->addTest(std::move(test2));

    // Act
    getTestGroup()->runAllTests();

    // Assert
    const auto& results = getTestGroup()->getResults();
    CHECK_EQUAL(2, results.size());
    CHECK_TRUE(results[0].isSuccess());
    CHECK_TRUE(results[1].isSuccess());
}

TEST (TestGroupTest, RunAllTests_TestFails)
{
    // Arrange
    auto test1 = std::make_unique<MockTestCase>();
    auto test2 = std::make_unique<MockTestCase>();
    test2->setExecuteResult(false, "Execution failed");

    getTestGroup()->addTest(std::move(test1));
    getTestGroup()->addTest(std::move(test2));

    // Act
    getTestGroup()->runAllTests();

    // Assert
    const auto& results = getTestGroup()->getResults();
    CHECK_EQUAL(2, results.size());
    CHECK_TRUE(results[0].isSuccess());
    CHECK_FALSE(results[1].isSuccess());
    STRCMP_EQUAL("Execution Failed: Execution failed", results[1].getMessage().c_str());
}

TEST (TestGroupTest, GetResults_BeforeRunning_ShouldReturnEmptyVector)
{
    // Arrange & Act
    const auto& results = getTestGroup()->getResults();

    // Assert
    CHECK_TRUE(results.empty());
}

TEST (TestGroupTest, RunAllTests_MultipleMixedResults_ShouldCollectAllResults)
{
    // Arrange
    auto test1 = std::make_unique<MockTestCase>();
    auto test2 = std::make_unique<MockTestCase>();
    auto test3 = std::make_unique<MockTestCase>();

    test1->setExecuteResult(true, "");
    test2->setExecuteResult(false, "Execution failed");
    test3->setExecuteResult(true, "");

    getTestGroup()->addTest(std::move(test1));
    getTestGroup()->addTest(std::move(test2));
    getTestGroup()->addTest(std::move(test3));

    // Act
    getTestGroup()->runAllTests();

    // Assert
    const auto& results = getTestGroup()->getResults();
    CHECK_EQUAL(3, results.size());
    CHECK_TRUE(results[0].isSuccess());
    CHECK_FALSE(results[1].isSuccess());
    CHECK_TRUE(results[2].isSuccess());
}

TEST (TestGroupTest, RunAllTests_NoTestsAdded_ShouldDoNothing)
{
    // Arrange
    // No tests added to the suite

    // Act
    getTestGroup()->runAllTests();

    // Assert
    const auto& results = getTestGroup()->getResults();
    CHECK_EQUAL(0, results.size());
}

TEST (TestGroupTest, AddTest_MultipleValidTestCases)
{
    // Arrange
    auto test1 = std::make_unique<MockTestCase>();
    auto test2 = std::make_unique<MockTestCase>();
    auto test3 = std::make_unique<MockTestCase>();

    // Act
    getTestGroup()->addTest(std::move(test1));
    getTestGroup()->addTest(std::move(test2));
    getTestGroup()->addTest(std::move(test3));

    // Assert
    getTestGroup()->runAllTests();
    const auto& results = getTestGroup()->getResults();
    CHECK_EQUAL(3, results.size());
}

TEST (TestGroupTest, RunAllTests_TestsWithTeardownFailure)
{
    // Arrange
    auto test1 = std::make_unique<MockTestCase>();
    test1->setTeardownResult(false, "Teardown failed");

    getTestGroup()->addTest(std::move(test1));

    // Act
    getTestGroup()->runAllTests();

    // Assert
    const auto& results = getTestGroup()->getResults();
    CHECK_EQUAL(1, results.size());
    CHECK_TRUE(results[0].isSuccess());
}

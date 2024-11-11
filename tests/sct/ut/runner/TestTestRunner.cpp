#include <CppUTest/TestHarness.h> // NOLINT(misc-include-cleaner)

#include <CppUTest/UtestMacros.h>

#include <memory>
#include <utility>

#include "Logger.hpp"
#include "MockTestCase.hpp"
#include "TestGroup.hpp"
#include "TestRunner.hpp"

TEST_GROUP (TestRunnerTest)
{
    void setup() override
    {
        m_test_runner = std::make_unique<TestRunner>();
        Logger::getInstance().disableFileOutput();
    }

    std::unique_ptr<TestRunner>& getRunner()
    {
        return m_test_runner;
    }

private:
    std::unique_ptr<TestRunner> m_test_runner;
};

TEST (TestRunnerTest, AddTestGroup_ValidGroup)
{
    // Arrange
    auto group = std::make_unique<TestGroup>();

    // Act
    getRunner()->addTestGroup(std::move(group));

    // Assert
    getRunner()->runAllTests();
    const auto& results = getRunner()->getAllResults();
    CHECK_EQUAL(0, results.size());
}

TEST (TestRunnerTest, RunAllTests_MultipleGroups)
{
    // Arrange
    auto group1 = std::make_unique<TestGroup>();
    auto group2 = std::make_unique<TestGroup>();

    auto test1 = std::make_unique<MockTestCase>();
    auto test2 = std::make_unique<MockTestCase>();
    auto test3 = std::make_unique<MockTestCase>();

    test2->setExecuteResult(false, "Execution failed");

    group1->addTest(std::move(test1));
    group2->addTest(std::move(test2));
    group2->addTest(std::move(test3));

    getRunner()->addTestGroup(std::move(group1));
    getRunner()->addTestGroup(std::move(group2));

    // Act
    getRunner()->runAllTests();

    // Assert
    const auto& results = getRunner()->getAllResults();
    CHECK_EQUAL(3, results.size());
    CHECK_TRUE(results[0].isSuccess());
    CHECK_FALSE(results[1].isSuccess());
    CHECK_TRUE(results[2].isSuccess());
}

TEST (TestRunnerTest, RunAllTests_NoGroupsAdded)
{
    // Arrange
    // No groups added to the runner

    // Act
    getRunner()->runAllTests();

    // Assert
    const auto& results = getRunner()->getAllResults();
    CHECK_EQUAL(0, results.size());
}

TEST (TestRunnerTest, RunAllTests_NullGroupInList)
{
    // Arrange
    getRunner()->addTestGroup(nullptr);

    // Act
    getRunner()->runAllTests();

    // Assert
    const auto& results = getRunner()->getAllResults();
    CHECK_EQUAL(0, results.size());
}

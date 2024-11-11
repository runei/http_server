#include "TestRunner.hpp"

#include <memory>
#include <utility>
#include <vector>

#include "Logger.hpp"
#include "TestCaseResult.hpp"
#include "TestGroup.hpp"

void TestRunner::addTestGroup(std::unique_ptr<TestGroup> test_group)
{
    if (!test_group)
    {
        Logger::getInstance().logError("Attempted to add a null test suite to the runner.");
        return;
    }
    m_test_groups.emplace_back(std::move(test_group));
}

void TestRunner::runAllTests()
{
    m_all_results.clear();

    Logger::getInstance().logInfo("Starting test execution...");

    for (const auto& group : m_test_groups)
    {
        group->runAllTests();
        const auto& results = group->getResults();
        m_all_results.insert(m_all_results.end(), results.begin(), results.end());
    }

    Logger::getInstance().logInfo("Test execution completed.");
}

const std::vector<TestCaseResult>& TestRunner::getAllResults() const
{
    return m_all_results;
}

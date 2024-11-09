#include "TestSuite.hpp"

#include <memory>
#include <utility>
#include <vector>

#include "Logger.hpp"
#include "TestCase.hpp"
#include "TestCaseResult.hpp"

void TestSuite::addTest(std::unique_ptr<TestCase> test_case)
{
    if (!test_case)
    {
        Logger::getInstance().logError("Attempted to add a null test case to the suite.");
        return;
    }

    m_test_cases.emplace_back(std::move(test_case));
}

void TestSuite::runAllTests()
{
    m_test_results.clear();

    for (const auto& test_case : m_test_cases)
    {
        test_case->run();
        TestCaseResult result = test_case->getResult();
        m_test_results.push_back(result);
        result.logResult();
    }
}

std::vector<TestCaseResult> TestSuite::getResults() const
{
    return m_test_results;
}

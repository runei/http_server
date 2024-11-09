#pragma once

#include <memory>
#include <vector>

#include "TestCase.hpp"
#include "TestCaseResult.hpp"

class TestSuite
{
public:
    void                                      addTest(std::unique_ptr<TestCase> test_case);
    void                                      runAllTests();
    [[nodiscard]] std::vector<TestCaseResult> getResults() const;

private:
    std::vector<std::unique_ptr<TestCase>> m_test_cases;
    std::vector<TestCaseResult>            m_test_results;
};

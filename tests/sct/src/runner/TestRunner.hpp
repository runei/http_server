#include <memory>
#include <vector>

#include "TestCaseResult.hpp"
#include "TestGroup.hpp"

class TestRunner
{
public:
    void addTestGroup(std::unique_ptr<TestGroup> test_group);

    void runAllTests();

    [[nodiscard]] const std::vector<TestCaseResult>& getAllResults() const;

private:
    std::vector<std::unique_ptr<TestGroup>> m_test_groups;
    std::vector<TestCaseResult>             m_all_results;
};

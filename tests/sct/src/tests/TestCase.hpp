#pragma once

#include <string>

#include "Definitions.hpp"
#include "TestCaseResult.hpp"

class TestCase
{
public:
    virtual ~TestCase() = default;

    void run();

    [[nodiscard]] TestCaseResult getResult() const;

protected:
    TestCase()                           = default;
    TestCase(const TestCase&)            = default;
    TestCase& operator=(const TestCase&) = default;
    TestCase(TestCase&&)                 = default;
    TestCase& operator=(TestCase&&)      = default;

    virtual OptionalErrorMessage setup()    = 0;
    virtual OptionalErrorMessage execute()  = 0;
    virtual OptionalErrorMessage teardown() = 0;

private:
    void recordSuccess(const std::string& message);
    void recordFailure(const std::string& message);

    TestCaseResult m_test_result;
};

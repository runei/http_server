#pragma once

#include <string>

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

    virtual bool setup(std::string& error_message)    = 0;
    virtual bool execute(std::string& error_message)  = 0;
    virtual bool teardown(std::string& error_message) = 0;

private:
    void recordSuccess(const std::string& message);
    void recordFailure(const std::string& message);

    TestCaseResult m_test_result;
};

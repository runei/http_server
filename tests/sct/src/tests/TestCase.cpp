#include "TestCase.hpp"

#include <chrono>
#include <string>

#include "Logger.hpp"

void TestCase::run()
{
    auto        start_time = std::chrono::steady_clock::now();
    std::string error_message;

    if (!setup(error_message))
    {
        recordFailure("Setup Failed: " + error_message);
    }
    else if (!execute(error_message))
    {
        recordFailure("Execution Failed: " + error_message);
    }
    else
    {
        recordSuccess("");
    }

    if (!teardown(error_message))
    {
        // Even if teardown fails, the test still passes
        Logger::getInstance().logError("Teardown Failed: " + error_message);
    }

    auto end_time = std::chrono::steady_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);
    m_test_result.setExecutionTime(duration);
}

TestCaseResult TestCase::getResult() const
{
    return m_test_result;
}

void TestCase::recordSuccess(const std::string& message)
{
    Logger::getInstance().logSuccess(message);
    m_test_result.setSuccess(true);
    m_test_result.setMessage(message);
}

void TestCase::recordFailure(const std::string& message)
{
    Logger::getInstance().logError(message);
    m_test_result.setSuccess(false);
    m_test_result.setMessage(message);
}

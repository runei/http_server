#include "TestCase.hpp"

#include <chrono>
#include <string>

#include "Logger.hpp"

void TestCase::run()
{
    auto start_time = std::chrono::steady_clock::now();

    auto setup_result = setup();

    if (setup_result)
    {
        recordFailure("Setup Failed: " + setup_result.value());
    }
    else
    {
        auto execute_result = execute();
        if (execute_result)
        {
            recordFailure("Execution Failed: " + execute_result.value());
        }
        else
        {
            recordSuccess("");
        }
    }

    auto teardown_result = teardown();

    if (teardown_result)
    {
        // Even if teardown fails, the test still passes
        Logger::getInstance().logError("Teardown Failed: " + teardown_result.value());
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

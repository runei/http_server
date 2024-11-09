#include "TestCaseResult.hpp"

#include <chrono>
#include <string>

#include "Logger.hpp"

void TestCaseResult::setSuccess(bool success)
{
    m_success = success;
}

bool TestCaseResult::isSuccess() const
{
    return m_success;
}

void TestCaseResult::setMessage(const std::string& message)
{
    m_message = message;
}

std::string TestCaseResult::getMessage() const
{
    return m_message;
}

void TestCaseResult::setExecutionTime(std::chrono::milliseconds execution_time)
{
    m_execution_time = execution_time;
}

std::chrono::milliseconds TestCaseResult::getExecutionTime() const
{
    return m_execution_time;
}

void TestCaseResult::logResult()
{
    Logger& logger = Logger::getInstance();

    if (isSuccess())
    {
        logger.logSuccess("Test Passed: " + getMessage());
    }
    else
    {
        logger.logError("Test Failed: " + getMessage());
    }

    logger.logInfo("Execution Time: " + std::to_string(m_execution_time.count()) + " ms");
}

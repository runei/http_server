#include <chrono>
#include <string>

#include "Logger.hpp"
#include "Result.hpp"

void Result::setSuccess(bool success)
{
    m_success = success;
}

bool Result::isSuccess() const
{
    return m_success;
}

void Result::setMessage(const std::string& message)
{
    m_message = message;
}

std::string Result::getMessage() const
{
    return m_message;
}

void Result::setExecutionTime(std::chrono::milliseconds execution_time)
{
    m_execution_time = execution_time;
}

std::chrono::milliseconds Result::getExecutionTime() const
{
    return m_execution_time;
}

void Result::logResult()
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

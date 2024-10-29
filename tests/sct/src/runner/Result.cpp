#include "Result.hpp"

#include <iomanip>
#include <sstream>

Result::Result() : m_logger(Logger::getInstance()) {}

void Result::logResult(const std::string& test_name, bool success, const std::string& message, double duration)
{
    m_results.emplace_back(test_name, success, message, duration);

    if (success)
    {
        m_logger.logSuccess("Test Passed: " + test_name + " - " + message);
    }
    else
    {
        m_logger.logError("Test Failed: " + test_name + " - " + message);
    }
}

std::string Result::getResults() const
{
    std::ostringstream oss;

    oss << getResultMessage("Test Name", "Result", "Message", "Duration (ms)");

    oss << std::string(SeparatorWidth, '-') << "\n";

    for (const auto& result : m_results)
    {
        std::string success_string = result.isSuccess() ? "PASS" : "FAIL";
        oss << getResultMessage(
            result.getTestName(), success_string, result.getMessage(), std::to_string(result.getDuration()));
    }

    return oss.str();
}

std::string Result::getResultMessage(const std::string& test_name,
                                     const std::string& result,
                                     const std::string& message,
                                     const std::string& duration)
{
    std::ostringstream oss;
    oss << std::left << std::setw(TestNameWidth) << test_name << std::setw(ResultWidth) << result
        << std::setw(MessageWidth) << message << duration << "\n";
    return oss.str();
}

void Result::clearResults()
{
    m_results.clear();
    m_logger.logInfo("All tests results have been cleared.");
}

#pragma once

#include <cstdint>
#include <string>
#include <utility>
#include <vector>

#include "Logger.hpp"

class Result
{
public:
    class TestOutcome;

    Result();

    void logResult(const std::string& test_name, bool success, const std::string& message, double duration);

    [[nodiscard]] std::string getResults() const;

    void clearResults();

private:
    [[nodiscard]] static std::string getResultMessage(const std::string& test_name,
                                                      const std::string& result,
                                                      const std::string& message,
                                                      const std::string& duration);

    // Display and alignment configuration
    static constexpr uint8_t TestNameWidth  = 20;
    static constexpr uint8_t ResultWidth    = 10;
    static constexpr uint8_t MessageWidth   = 50;
    static constexpr uint8_t SeparatorWidth = 80;

    std::vector<TestOutcome> m_results;
    Logger*                  m_logger;
};

class Result::TestOutcome
{
public:
    explicit TestOutcome(std::string name, bool is_success, std::string msg, double time)
        : m_test_name(std::move(name)), m_success(is_success), m_message(std::move(msg)), m_duration(time)
    {
    }

    [[nodiscard]] std::string getTestName() const { return m_test_name; }
    [[nodiscard]] bool        isSuccess() const { return m_success; }
    [[nodiscard]] std::string getMessage() const { return m_message; }
    [[nodiscard]] double      getDuration() const { return m_duration; }

private:
    std::string m_test_name;
    bool        m_success;
    std::string m_message;
    double      m_duration;
};

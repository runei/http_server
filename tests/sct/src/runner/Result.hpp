#pragma once

#include <chrono>
#include <string>

class Result
{
public:
    void                                    setSuccess(bool success);
    [[nodiscard]] bool                      isSuccess() const;
    void                                    setMessage(const std::string& message);
    [[nodiscard]] std::string               getMessage() const;
    void                                    setExecutionTime(std::chrono::milliseconds execution_time);
    [[nodiscard]] std::chrono::milliseconds getExecutionTime() const;
    void                                    logResult();

private:
    bool                      m_success{false};
    std::string               m_message;
    std::chrono::milliseconds m_execution_time{};
};

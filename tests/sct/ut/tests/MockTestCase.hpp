#pragma once

#include <string>

#include "TestCase.hpp"

class MockTestCase : public TestCase
{
public:
    MockTestCase(const MockTestCase&)            = delete;
    MockTestCase& operator=(const MockTestCase&) = delete;
    MockTestCase(MockTestCase&&)                 = delete;
    MockTestCase& operator=(MockTestCase&&)      = delete;

    MockTestCase()           = default;
    ~MockTestCase() override = default;

    // Setters for mock behaviors
    void setSetupResult(bool result, const std::string& error_message);
    void setExecuteResult(bool result, const std::string& error_message);
    void setTeardownResult(bool result, const std::string& error_message);

    // Getters to verify if methods were called
    [[nodiscard]] bool wasSetupCalled() const;
    [[nodiscard]] bool wasExecuteCalled() const;
    [[nodiscard]] bool wasTeardownCalled() const;

protected:
    bool setup(std::string& error_message) override;
    bool execute(std::string& error_message) override;
    bool teardown(std::string& error_message) override;

private:
    // Mock behaviors
    bool m_setup_result{true};
    bool m_execute_result{true};
    bool m_teardown_result{true};

    std::string m_setup_error_message;
    std::string m_execute_error_message;
    std::string m_teardown_error_message;

    bool m_setup_called{false};
    bool m_execute_called{false};
    bool m_teardown_called{false};
};

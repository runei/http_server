#include <CppUTest/TestHarness.h> // NOLINT(misc-include-cleaner)

#include <CppUTest/UtestMacros.h>

#include <cstdint>
#include <memory>
#include <optional>
#include <string>

#include "Definitions.hpp"
#include "Logger.hpp"
#include "ServerTestCase.hpp"
#include "TestCaseResult.hpp"

class MockServerTestCase : public ServerTestCase
{
public:
    explicit MockServerTestCase(uint16_t port) : ServerTestCase(port) {}

    void setExecuteServerTestResult(bool result, const std::string& error_message)
    {
        m_execute_result        = result;
        m_execute_error_message = error_message;
    }

    [[nodiscard]] bool wasExecuteServerTestCalled() const { return m_execute_called; }

protected:
    OptionalErrorMessage executeServerTest() override
    {
        m_execute_called = true;
        if (m_execute_result)
        {
            return std::nullopt;
        }
        return m_execute_error_message;
    }

private:
    bool        m_execute_result{true};
    std::string m_execute_error_message;
    bool        m_execute_called{false};
};

TEST_GROUP (ServerTestCaseTest)
{
    void setup() override
    {
        m_test_case = std::make_unique<MockServerTestCase>(Port);
        Logger::getInstance().disableFileOutput();
    }

    std::unique_ptr<MockServerTestCase>& getTestCase()
    {
        return m_test_case;
    }

private:
    static constexpr uint16_t Port = 8080;

    std::unique_ptr<MockServerTestCase> m_test_case;
};

TEST (ServerTestCaseTest, SuccessfulExecution)
{
    // Arrange
    getTestCase()->setExecuteServerTestResult(true, "");

    // Act
    getTestCase()->run();

    // Assert
    CHECK_TRUE(getTestCase()->wasExecuteServerTestCalled());

    const TestCaseResult& test_result = getTestCase()->getResult();
    CHECK_TRUE(test_result.isSuccess());
}

TEST (ServerTestCaseTest, ExecuteServerTestFails)
{
    // Arrange
    getTestCase()->setExecuteServerTestResult(false, "Server test execution failed");

    // Act
    getTestCase()->run();

    // Assert
    CHECK_TRUE(getTestCase()->wasExecuteServerTestCalled());

    const TestCaseResult& test_result = getTestCase()->getResult();
    CHECK_FALSE(test_result.isSuccess());
    STRCMP_EQUAL("Execution Failed: Server test execution failed", test_result.getMessage().c_str());
}

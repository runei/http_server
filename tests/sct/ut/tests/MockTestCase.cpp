#include "MockTestCase.hpp"

#include <optional>
#include <string>

void MockTestCase::setSetupResult(bool result, const std::string& error_message)
{
    if (result)
    {
        m_setup_result = std::nullopt;
    }
    else
    {
        m_setup_result = error_message;
    }
}

void MockTestCase::setExecuteResult(bool result, const std::string& error_message)
{
    if (result)
    {
        m_execute_result = std::nullopt;
    }
    else
    {
        m_execute_result = error_message;
    }
}

void MockTestCase::setTeardownResult(bool result, const std::string& error_message)
{
    if (result)
    {
        m_teardown_result = std::nullopt;
    }
    else
    {
        m_teardown_result = error_message;
    }
}

bool MockTestCase::wasSetupCalled() const
{
    return m_setup_called;
}

bool MockTestCase::wasExecuteCalled() const
{
    return m_execute_called;
}

bool MockTestCase::wasTeardownCalled() const
{
    return m_teardown_called;
}

OptionalErrorMessage MockTestCase::setup()
{
    m_setup_called = true;
    return m_setup_result;
}

OptionalErrorMessage MockTestCase::execute()
{
    m_execute_called = true;
    return m_execute_result;
}

OptionalErrorMessage MockTestCase::teardown()
{
    m_teardown_called = true;
    return m_teardown_result;
}

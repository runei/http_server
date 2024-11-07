#include "MockTestCase.hpp"

#include <string>

void MockTestCase::setSetupResult(bool result, const std::string& error_message)
{
    m_setup_result        = result;
    m_setup_error_message = error_message;
}

void MockTestCase::setExecuteResult(bool result, const std::string& error_message)
{
    m_execute_result        = result;
    m_execute_error_message = error_message;
}

void MockTestCase::setTeardownResult(bool result, const std::string& error_message)
{
    m_teardown_result        = result;
    m_teardown_error_message = error_message;
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

bool MockTestCase::setup(std::string& error_message)
{
    m_setup_called = true;
    error_message  = m_setup_error_message;
    return m_setup_result;
}

bool MockTestCase::execute(std::string& error_message)
{
    m_execute_called = true;
    error_message    = m_execute_error_message;
    return m_execute_result;
}

bool MockTestCase::teardown(std::string& error_message)
{
    m_teardown_called = true;
    error_message     = m_teardown_error_message;
    return m_teardown_result;
}

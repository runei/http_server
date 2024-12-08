#include "ServerTestCase.hpp"

#include <cstdint>
#include <memory>
#include <optional>
#include <thread>

#include "Definitions.hpp"
#include "Logger.hpp"
#include "Server.hpp"

ServerTestCase::ServerTestCase(uint16_t port) : m_port(port), m_server(nullptr) {}

OptionalErrorMessage ServerTestCase::setup()
{
    Logger::getInstance().logInfo("ServerTestCase: Setting up server environment.");

    m_server = std::make_unique<Server>(m_port);

    m_server_thread = std::thread([this]() { m_server->start(); });

    m_server->waitForServerToStart();

    Logger::getInstance().logInfo("ServerTestCase: Server started successfully.");

    return std::nullopt;
}

OptionalErrorMessage ServerTestCase::execute()
{
    Logger::getInstance().logInfo("ServerTestCase: Executing server test.");

    return executeServerTest();
}

OptionalErrorMessage ServerTestCase::teardown()
{
    Logger::getInstance().logInfo("ServerTestCase: Tearing down server environment.");

    if (m_server)
    {
        m_server->stop();
        Logger::getInstance().logInfo("ServerTestCase: Server stopped successfully.");
        m_server_thread.join();
        m_server.reset();
    }
    else
    {
        return "Server instance is null.";
    }

    return std::nullopt;
}

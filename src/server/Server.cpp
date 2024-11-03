#include "Server.hpp"

#include <cstdint>
#include <memory>
#include <mutex>
#include <optional>

#include "FileRequestHandler.hpp"
#include "SocketManager.hpp"

Server::Server(uint16_t port) : m_port(port), m_dispatcher(std::make_unique<FileRequestHandler>()) {}

Server::~Server()
{
    stop();
}

void Server::start()
{
    setupSocket();
    listenForConnections();
}

void Server::stop()
{
    updateServerRunningState(false);
    SocketManager::getInstance().closeSocket();
}

void Server::waitForServerToStart()
{
    std::unique_lock<std::mutex> lock(m_mutex);
    m_condition.wait(lock, [this]() { return this->isServerRunning(); });
}

void Server::setupSocket() const
{
    auto& socket_manager = SocketManager::getInstance();
    socket_manager.createSocket(m_port);
}

void Server::listenForConnections()
{
    auto& socket = SocketManager::getInstance();
    socket.listenSocket(MaxNumberOfConnections);
    updateServerRunningState(true);

    while (isServerRunning())
    {
        std::optional<int> client = socket.acceptConnection();
        if (client.has_value())
        {
            m_dispatcher.handleRequest(client.value());
        }
    }
}

void Server::updateServerRunningState(bool is_running)
{
    {
        const std::lock_guard<std::mutex> lock(m_mutex);

        m_is_running = is_running;
    }

    m_condition.notify_all();
}

bool Server::isServerRunning() const
{
    return m_is_running;
}

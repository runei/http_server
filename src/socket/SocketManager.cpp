#include "SocketManager.hpp"

#include <sys/socket.h>

#include <bit>
#include <stdexcept>

#include <unistd.h>

SocketManager& SocketManager::getInstance()
{
    static SocketManager socket_manager;
    return socket_manager;
}

void SocketManager::createSocket(uint16_t port)
{
    if (isSocketCreated())
    {
        throw std::runtime_error("Socket already created");
    }

    m_server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (m_server_socket < 0)
    {
        throw std::runtime_error("Failed to create socket");
    }

    bindSocket(port);
}

void SocketManager::listenSocket(int n_connections)
{
    if (!isSocketCreated())
    {
        throw std::runtime_error("Socket not created yet");
    }

    if (listen(m_server_socket, n_connections) < 0)
    {
        throw std::runtime_error("Failed to listen socket");
    }
}

int SocketManager::acceptConnection()
{
    if (!isSocketCreated())
    {
        throw std::runtime_error("Socket not created yet");
    }

    sockaddr_in client_address{};
    socklen_t   client_len = sizeof(client_address);

    return accept(m_server_socket, std::bit_cast<sockaddr*>(&client_address), &client_len);
}

void SocketManager::closeSocket()
{
    if (isSocketCreated())
    {
        close(m_server_socket);
        m_server_socket = InactiveServer;
    }
}

void SocketManager::bindSocket(uint16_t port)
{
    setAddress(port);

    if (bind(m_server_socket, std::bit_cast<sockaddr*>(&m_address), sizeof(m_address)) < 0)
    {
        throw std::runtime_error("Failed to bind socket");
    }
}

void SocketManager::setAddress(uint16_t port)
{
    m_address.sin_family      = AF_INET;
    m_address.sin_addr.s_addr = INADDR_ANY;
    m_address.sin_port        = htons(port);
}

[[nodiscard]] bool SocketManager::isSocketCreated() const
{
    return m_server_socket != InactiveServer;
}

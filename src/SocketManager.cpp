#include "SocketManager.hpp"

#include <sys/socket.h>

#include <stdexcept>
#include <string>

SocketManager& SocketManager::getInstance()
{
    static SocketManager socket_manager;
    return socket_manager;
}

void SocketManager::createSocket()
{
    m_server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (m_server_fd < 0)
    {
        throw std::runtime_error("Failed to create socket");
    }
}

void SocketManager::bindSocket(uint16_t port)
{
    setAddress(port);

    if (bind(m_server_fd, reinterpret_cast<sockaddr*>(&m_address), sizeof(m_address)) < 0)
    {
        throw std::runtime_error("Failed to bind socket");
    }
}

void SocketManager::listenSocket(int n_connections)
{
    if (listen(m_server_fd, n_connections) < 0)
    {
        throw std::runtime_error("Failed to listen socket");
    }
}

int SocketManager::acceptConnection()
{
    sockaddr_in client_address;
    socklen_t   client_len = sizeof(client_address);

    return accept(m_server_fd, reinterpret_cast<sockaddr*>(&m_address), &client_len);
}

void SocketManager::setAddress(uint16_t port)
{
    m_address.sin_family      = AF_INET;
    m_address.sin_addr.s_addr = INADDR_ANY;
    m_address.sin_port        = htons(port);
}

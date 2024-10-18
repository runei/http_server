#include "SocketManager.hpp"

#include <sys/socket.h>

#include <bit>

#include <unistd.h>

#include "SocketException.hpp"

SocketManager& SocketManager::getInstance()
{
    static SocketManager socket_manager;
    return socket_manager;
}

void SocketManager::createSocket(uint16_t port)
{
    if (isSocketCreated())
    {
        throw SocketException("SocketManager: Socket already created");
    }

    m_server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (m_server_socket < 0)
    {
        throw SocketException("SocketManager: Failed to create socket", errno);
    }

    setReusableAddress();

    bindSocket(port);
}

void SocketManager::listenSocket(int n_connections)
{
    if (!isSocketCreated())
    {
        throw SocketException("SocketManager: Socket not created yet");
    }

    if (listen(m_server_socket, n_connections) < 0)
    {
        throw SocketException("SocketManager: Failed to listen socket", errno);
    }
}

[[nodiscard]] std::optional<int> SocketManager::acceptConnection()
{
    if (!isSocketCreated())
    {
        throw SocketException("SocketManager: Socket not created yet");
    }

    fd_set read_fd;
    FD_ZERO(&read_fd);
    FD_SET(m_server_socket, &read_fd);

    timeval timeout{};
    timeout.tv_sec = 1;

    int activity = select(m_server_socket + 1, &read_fd, nullptr, nullptr, &timeout);

    if (activity > 0 && FD_ISSET(m_server_socket, &read_fd))
    {
        sockaddr_in client_address{};
        socklen_t   client_len = sizeof(client_address);

        int client_socket = accept(m_server_socket, std::bit_cast<sockaddr*>(&client_address), &client_len);
        if (client_socket < 0)
        {
            return std::nullopt;
        }

        return client_socket;
    }

    return std::nullopt;
}

void SocketManager::closeSocket()
{
    if (isSocketCreated())
    {
        if (close(m_server_socket) < 0)
        {
            throw SocketException("SocketManager: Failed to close socket:", errno);
        }
        m_server_socket = InactiveServer;
    }
}

void SocketManager::bindSocket(uint16_t port)
{
    setAddress(port);

    if (bind(m_server_socket, std::bit_cast<sockaddr*>(&m_address), sizeof(m_address)) < 0)
    {
        closeSocket();
        throw SocketException("SocketManager: Failed to bind socket", errno);
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

void SocketManager::setReusableAddress()
{
    int opt = 1;
    if (setsockopt(m_server_socket, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0)
    {
        closeSocket();
        throw SocketException("Failed to set SO_REUSEADDR option", errno);
    }
}

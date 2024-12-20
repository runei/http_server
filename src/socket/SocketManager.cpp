#include "SocketManager.hpp"

#include <sys/poll.h>
#include <sys/socket.h>

#include <bit>
#include <cerrno>
#include <cstdint>
#include <optional>

#include <netinet/in.h>
#include <poll.h>
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

    pollfd fds{};
    fds.fd     = m_server_socket;
    fds.events = POLLIN;

    const int ret = poll(&fds, 1, TimeoutMs);

    if (ret > 0 && fds.events == POLLIN)
    {
        const sockaddr_in client_address{};
        socklen_t         client_len = sizeof(client_address);

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

    // NOLINTNEXTLINE(misc-include-cleaner)
    if (setsockopt(m_server_socket, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0)
    {
        closeSocket();
        throw SocketException("Failed to set SO_REUSEADDR option", errno);
    }
}

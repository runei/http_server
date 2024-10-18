#pragma once

#include <optional>

#include <netinet/in.h>

class SocketManager
{
public:
    // Deleted copy constructor and assignment operator to ensure singleton
    SocketManager(const SocketManager&)            = delete;
    SocketManager& operator=(const SocketManager&) = delete;

    SocketManager(SocketManager&&) noexcept            = delete;
    SocketManager& operator=(SocketManager&&) noexcept = delete;

    ~SocketManager() = default;

    static SocketManager&            getInstance();
    void                             createSocket(uint16_t port);
    void                             listenSocket(int n_connections);
    [[nodiscard]] std::optional<int> acceptConnection();
    void                             closeSocket();

private:
    SocketManager() = default;

    void               bindSocket(uint16_t port);
    void               setAddress(uint16_t port);
    [[nodiscard]] bool isSocketCreated() const;
    void               setReusableAddress();

    static constexpr int InactiveServer = -1;

    int         m_server_socket{InactiveServer};
    sockaddr_in m_address{};
};

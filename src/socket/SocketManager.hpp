#pragma once

#include <netinet/in.h>

class SocketManager
{
public:
    // Deleted copy constructor and assignment operator to ensure singleton
    SocketManager(const SocketManager&)            = delete;
    SocketManager& operator=(const SocketManager&) = delete;

    static SocketManager& getInstance();
    void                  createSocket(uint16_t port);
    void                  listenSocket(int n_connections);
    int                   acceptConnection();
    void                  closeSocket();

private:
    SocketManager() = default;

    void               bindSocket(uint16_t port);
    void               setAddress(uint16_t port);
    [[nodiscard]] bool isSocketCreated() const;

    static constexpr int INACTIVE_SERVER = -1;

    int         m_server_socket{INACTIVE_SERVER};
    sockaddr_in m_address{};
};

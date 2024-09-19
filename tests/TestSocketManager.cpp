#include "CppUTest/TestHarness.h"

#include <bit>
#include <stdexcept>
#include <thread>

#include <arpa/inet.h>

#include "SocketManager.hpp"

void simulateClientConnection(uint16_t port)
{
    int client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket < 0)
    {
        throw std::runtime_error("Failed to create client socket");
    }

    sockaddr_in server_address{};
    server_address.sin_family = AF_INET;
    inet_pton(AF_INET, "127.0.0.1", &(server_address.sin_addr));
    server_address.sin_port = htons(port);

    if (connect(client_socket, std::bit_cast<sockaddr*>(&server_address), sizeof(server_address)) < 0)
    {
        close(client_socket);
        throw std::runtime_error("Failed to connect to server");
    }
    close(client_socket);
}

TEST_GROUP (SocketManagerTest)
{
    static constexpr uint16_t Port              = 8080;
    static constexpr int      NumberConnections = 10;

    void setup() override {}

    void teardown() override
    {
        SocketManager::getInstance().closeSocket();
    }
};

TEST (SocketManagerTest, CreateSocket)
{
    // Arrange
    SocketManager& socket_manager = SocketManager::getInstance();

    // Act & Assert
    try
    {
        socket_manager.createSocket(Port);
        CHECK(true);
    }
    catch (...)
    {
        FAIL("Exception thrown when it should not have been");
    }
}

TEST (SocketManagerTest, CreateSocketWhenAlreadyCreated)
{
    // Arrange
    SocketManager& socket_manager = SocketManager::getInstance();
    socket_manager.createSocket(Port);

    // Act & Assert
    CHECK_THROWS(std::runtime_error, socket_manager.createSocket(8081));
}

TEST (SocketManagerTest, ListenSocket)
{
    // Arrange
    SocketManager& socket_manager = SocketManager::getInstance();
    socket_manager.createSocket(Port);

    // Act & Assert
    try
    {
        socket_manager.listenSocket(NumberConnections);
        CHECK(true);
    }
    catch (...)
    {
        FAIL("Exception thrown when it should not have been");
    }
}

TEST (SocketManagerTest, AcceptConnection)
{
    // Arrange
    SocketManager& socket_manager = SocketManager::getInstance();
    socket_manager.createSocket(Port);
    socket_manager.listenSocket(NumberConnections);

    // Act
    std::thread client_thread(simulateClientConnection, Port);

    // Assert
    try
    {
        socket_manager.acceptConnection();
        CHECK(true);
    }
    catch (...)
    {
        FAIL("Exception thrown when it should not have been");
    }

    client_thread.join();
}

TEST (SocketManagerTest, CloseSocket)
{
    // Arrange
    SocketManager& socket_manager = SocketManager::getInstance();
    socket_manager.createSocket(Port);

    // Act
    socket_manager.closeSocket();

    // Assert
    CHECK_THROWS(std::runtime_error, socket_manager.listenSocket(NumberConnections));
}
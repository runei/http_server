#include <CppUTest/TestHarness.h>

#include <memory>
#include <thread>

#include "Client.hpp"
#include "Server.hpp"

TEST_GROUP (ServerTest)
{
    static constexpr uint16_t Port = 8080;

    void setup() override
    {
        m_server        = std::make_unique<Server>(Port);
        m_server_thread = std::jthread([this]() { m_server->start(); });

        m_server->waitForServerToStart();
    }

    void teardown() override
    {
        m_server->stop();
    }

private:
    std::unique_ptr<Server> m_server;
    std::jthread            m_server_thread;
};

TEST (ServerTest, ConnectsAndSendResponse)
{
    // Arrange
    std::string raw_request = "GET /test.html HTTP/1.1\r\nHost: localhost\r\n\r\n";
    std::string expected =
        "HTTP/1.1 200 OK\nContent-Length: 40\nContent-Type: text/html\n\n<html><body>Hello, World!</body></html>\n";

    Client client;
    bool   connected = client.connectToServer("127.0.0.1", Port);
    CHECK_TRUE(connected);

    // Act
    bool request_sent = client.sendRequest(raw_request);
    CHECK_TRUE(request_sent);

    std::string response = client.getResponse();

    // Assert
    STRCMP_EQUAL(expected.data(), response.data());
}

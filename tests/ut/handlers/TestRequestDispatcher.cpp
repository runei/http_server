#include <CppUTest/TestHarness.h> // NOLINT(misc-include-cleaner)

#include <CppUTest/UtestMacros.h>
#include <CppUTestExt/MockSupport.h>

#include <sys/types.h>

#include <cstddef>
#include <memory>
#include <string>

#include "Definitions.hpp"
#include "HttpRequest.hpp"
#include "HttpResponse.hpp"
#include "HttpStatusCode.hpp"
#include "IRequestHandler.hpp"
#include "RequestDispatcher.hpp"

extern "C"
{
    ssize_t recv(int sock_fd, void* buf, size_t len, int flags)
    {
        return mock()
            .actualCall("recv")
            .withParameter("sock_fd", sock_fd)
            .withParameter("len", len)
            .withParameter("flags", flags)
            .withOutputParameter("buf", buf)
            .returnLongIntValue();
    }

    ssize_t send(int sock_fd, const char* buf, size_t len, int flags)
    {
        return mock()
            .actualCall("send")
            .withParameter("sock_fd", sock_fd)
            .withParameter("buf", buf)
            .withParameter("len", len)
            .withParameter("flags", flags)
            .returnLongIntValue();
    }

    int close(int _fd)
    {
        return mock().actualCall("close").withParameter("_fd", _fd).returnIntValue();
    }
}

class DummyRequestHandler : public IRequestHandler
{
public:
    HttpResponse handle(const HttpRequest& http_request) override
    {
        return HttpResponse::Builder()
            .setStatusCode(HttpStatusCode::OK)
            .setHttpVersion(http_request.getHttpVersion())
            .build();
    }
};

TEST_GROUP (RequestDispatcherTest)
{
    void teardown() override
    {
        mock().clear();
    }
};

TEST (RequestDispatcherTest, HandleRequest_SuccessfulRequest)
{
    // Arrange
    RequestDispatcher dispatcher{std::make_unique<DummyRequestHandler>()};
    const int         client_socket     = 1;
    const std::string raw_request       = "GET /index.html HTTP/1.1\r\nHost: localhost\r\n\r\n";
    const std::string expected_response = "HTTP/1.1 200 OK\n\n";

    // Mocks
    mock()
        .expectOneCall("recv")
        .withParameter("sock_fd", client_socket)
        .withOutputParameterReturning("buf", raw_request.data(), raw_request.size())
        .withParameter("len", BufferSize)
        .withParameter("flags", 0)
        .andReturnValue(static_cast<ssize_t>(raw_request.size()));

    mock()
        .expectOneCall("send")
        .withParameter("sock_fd", client_socket)
        .withParameter("buf", expected_response.data())
        .withParameter("len", expected_response.size())
        .withParameter("flags", 0)
        .andReturnValue(static_cast<ssize_t>(expected_response.size()));

    mock().expectOneCall("close").withParameter("_fd", client_socket).andReturnValue(1);

    // Act
    dispatcher.handleRequest(client_socket);

    // Assert
    mock().checkExpectations();
}

TEST (RequestDispatcherTest, HandleRequest_NotSuccessfulRequest)
{
    // Arrange
    RequestDispatcher dispatcher{std::make_unique<DummyRequestHandler>()};
    const int         client_socket = 1;
    const std::string raw_request   = "GET /index.html HTTP/1.1\n";
    const std::string expected_response =
        "HTTP/1.1 400 Bad Request\nContent-Type: text/html\n\n<html><head><title>400 Bad "
        "Request</title></head><body><h1>400 Bad Request</h1><p>An error occurred: 400 Bad Request</p></body></html>";

    // Mocks
    mock()
        .expectOneCall("recv")
        .withParameter("sock_fd", client_socket)
        .withOutputParameterReturning("buf", raw_request.data(), raw_request.size())
        .withParameter("len", BufferSize)
        .withParameter("flags", 0)
        .andReturnValue(static_cast<ssize_t>(raw_request.size()));

    mock()
        .expectOneCall("send")
        .withParameter("sock_fd", client_socket)
        .withParameter("buf", expected_response.data())
        .withParameter("len", expected_response.size())
        .withParameter("flags", 0)
        .andReturnValue(static_cast<ssize_t>(expected_response.size()));

    mock().expectOneCall("close").withParameter("_fd", client_socket).andReturnValue(1);

    // Act
    dispatcher.handleRequest(client_socket);

    // Assert
    mock().checkExpectations();
}

TEST (RequestDispatcherTest, HandleRequest_LargeRequest)
{
    // Arrange
    RequestDispatcher dispatcher{std::make_unique<DummyRequestHandler>()};
    const int         client_socket = 1;
    constexpr size_t  TotalSize     = BufferSize + (BufferSize / 2);

    // Simulate a request larger than Buffersize bytes (let's use 5000 bytes as an example)
    const std::string init_request      = "GET /index.html HTTP/1.1\r\nHost: localhost\r\n\r\n";
    const std::string raw_request_part1 = init_request + std::string(BufferSize - init_request.size(), 'A');
    const std::string raw_request_part2(TotalSize - BufferSize, 'B');
    const std::string expected_response = "HTTP/1.1 200 OK\n\n";

    // First recv call to return the first Buffersize bytes
    mock()
        .expectOneCall("recv")
        .withParameter("sock_fd", client_socket)
        .withOutputParameterReturning("buf", raw_request_part1.data(), raw_request_part1.size())
        .withParameter("len", BufferSize)
        .withParameter("flags", 0)
        .andReturnValue(static_cast<ssize_t>(raw_request_part1.size()));

    // Second recv call to return the remaining bytes
    mock()
        .expectOneCall("recv")
        .withParameter("sock_fd", client_socket)
        .withOutputParameterReturning("buf", raw_request_part2.data(), raw_request_part2.size())
        .withParameter("len", BufferSize)
        .withParameter("flags", 0)
        .andReturnValue(static_cast<ssize_t>(raw_request_part2.size()));

    mock()
        .expectOneCall("send")
        .withParameter("sock_fd", client_socket)
        .withParameter("buf", expected_response.data())
        .withParameter("len", expected_response.size())
        .withParameter("flags", 0)
        .andReturnValue(static_cast<ssize_t>(expected_response.size()));

    mock().expectOneCall("close").withParameter("_fd", client_socket).andReturnValue(1);

    // Act
    dispatcher.handleRequest(client_socket);

    // Assert
    mock().checkExpectations();
}

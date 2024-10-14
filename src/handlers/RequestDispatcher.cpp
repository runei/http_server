#include "RequestDispatcher.hpp"

#include <sys/socket.h>

#include "ErrorHandler.hpp"
#include "RequestParser.hpp"

RequestDispatcher::RequestDispatcher(std::unique_ptr<IRequestHandler> request_handler)
    : m_request_handler(std::move(request_handler))
{
}

void RequestDispatcher::handleRequest(int client_socket)
{
    std::string raw_request = readFromSocket(client_socket);

    auto request = RequestParser::parse(raw_request);

    std::string response;
    if (!request.success())
    {
        auto http_response = ErrorHandler::handleError(request.status());
        response           = http_response.buildResponse();
    }
    else
    {
        auto http_response = m_request_handler->handle(request.value());
        response           = http_response.buildResponse();
    }

    auto bytes_sent = send(client_socket, response.data(), response.size(), 0);
    if (bytes_sent == -1)
    {
        close(client_socket);
    }
    close(client_socket);
}

std::string RequestDispatcher::readFromSocket(int client_socket)
{
    static constexpr int BufferSize = 4096;

    std::array<char, BufferSize> buffer{};
    std::string                  raw_request;

    ssize_t bytes_read = -1;

    while ((bytes_read = recv(client_socket, buffer.data(), buffer.size(), 0)) > 0)
    {
        raw_request.append(buffer.data(), bytes_read);

        if (bytes_read < BufferSize)
        {
            break;
        }
    }

    return raw_request;
}

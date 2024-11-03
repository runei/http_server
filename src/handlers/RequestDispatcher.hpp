#pragma once

#include <memory>
#include <string>

#include "IRequestHandler.hpp"

class RequestDispatcher
{
public:
    explicit RequestDispatcher(std::unique_ptr<IRequestHandler> request_handler);

    void handleRequest(int client_socket);

private:
    static std::string readFromSocket(int client_socket);

    std::unique_ptr<IRequestHandler> m_request_handler;
};

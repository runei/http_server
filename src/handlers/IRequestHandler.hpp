#pragma once

#include "HttpRequest.hpp"
#include "HttpResponse.hpp"

class IRequestHandler
{
public:
    IRequestHandler()          = default;
    virtual ~IRequestHandler() = default;

    // Copy constructor and assignment
    IRequestHandler(const IRequestHandler&)            = delete;
    IRequestHandler& operator=(const IRequestHandler&) = delete;

    // Move constructor and assignment
    IRequestHandler(IRequestHandler&&)            = delete;
    IRequestHandler& operator=(IRequestHandler&&) = delete;

    virtual HttpResponse handle(const HttpRequest& http_request) = 0;
};

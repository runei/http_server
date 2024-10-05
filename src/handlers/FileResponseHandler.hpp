#pragma once

#include "HttpRequest.hpp"
#include "HttpResponse.hpp"

class FileResponseHandler
{
public:
    static HttpResponse handleRequest(const HttpRequest& request);

private:
    static std::optional<std::string> readFileContents(const std::string& file_path);
};

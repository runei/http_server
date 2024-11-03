#pragma once

#include <optional>
#include <string>

#include "HttpRequest.hpp"
#include "HttpResponse.hpp"
#include "IRequestHandler.hpp"

class FileRequestHandler : public IRequestHandler
{
public:
    HttpResponse handle(const HttpRequest& request) override;

private:
    static std::optional<std::string> readFileContents(const std::string& file_path);
};

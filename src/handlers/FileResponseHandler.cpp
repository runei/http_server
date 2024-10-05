#include "FileResponseHandler.hpp"

#include <fstream>
#include <sstream>

#include "CommonFunctions.hpp"
#include "Definitions.hpp"
#include "ErrorHandler.hpp"

HttpResponse FileResponseHandler::handleRequest(const HttpRequest& request)
{
    std::string file_path = CommonFunctions::getStaticFolderPath() + request.getUrl();

    auto file_contents = readFileContents(file_path);
    if (!file_contents)
    {
        return ErrorHandler::handleError(HttpStatusCode::NotFound);
    }

    HttpResponse::Builder builder;
    builder.setStatusCode(HttpStatusCode::OK)
        .setBody(file_contents.value())
        .setHttpVersion(request.getHttpVersion())
        .addHeader("Content-Type", "text/html")
        .addHeader("Content-Length", std::to_string(file_contents->size()));

    return builder.build();
}

std::optional<std::string> FileResponseHandler::readFileContents(const std::string& file_path)
{
    std::ifstream file(file_path, std::ios::in | std::ios::binary);
    if (!file)
    {
        return std::nullopt;
    }

    std::ostringstream file_stream;
    file_stream << file.rdbuf();

    return file_stream.str();
}

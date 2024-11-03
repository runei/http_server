#include "ErrorHandler.hpp"

#include <sstream>
#include <string>

#include "HttpResponse.hpp"
#include "HttpStatusCode.hpp"
#include "HttpVersion.hpp"

HttpResponse ErrorHandler::handleError(HttpStatusCode status_code)
{
    HttpResponse::Builder builder;

    builder.setHttpVersion(HttpVersion::Http11).setStatusCode(status_code).setBody(generateErrorMessage(status_code));

    builder.addHeader("Content-Type", "text/html");

    return builder.build();
}

std::string ErrorHandler::generateErrorMessage(HttpStatusCode status_code)
{
    auto status_description = HttpStatusCodeHelper::getHttpStatusDescription(status_code);

    std::ostringstream error_page;
    error_page << "<html><head><title>" << status_description << "</title></head>"
               << "<body><h1>" << status_description << "</h1>"
               << "<p>An error occurred: " << status_description << "</p>"
               << "</body></html>";

    return error_page.str();
}

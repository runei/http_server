#pragma once

#include <string>

#include "HttpResponse.hpp"
#include "HttpStatusCode.hpp"

class ErrorHandler
{
public:
    static HttpResponse handleError(HttpStatusCode status_code);

private:
    static std::string generateErrorMessage(HttpStatusCode status_code);
};

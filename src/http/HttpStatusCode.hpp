#pragma once

#include <map>
#include <string_view>

enum class HttpStatusCode
{
    // 2xx Success
    OK        = 200,
    Created   = 201,
    NoContent = 204,

    // 3xx Redirection
    MovedPermanently = 301,
    Found            = 302,
    NotModified      = 304,

    // 4xx Client Errors
    BadRequest           = 400,
    Unauthorized         = 401,
    Forbidden            = 403,
    NotFound             = 404,
    MethodNotAllowed     = 405,
    RequestTimeout       = 408,
    Conflict             = 409,
    Gone                 = 410,
    PayloadTooLarge      = 413,
    UnsupportedMediaType = 415,
    TooManyRequests      = 429,

    // 5xx Server Errors
    InternalServerError     = 500,
    NotImplemented          = 501,
    BadGateway              = 502,
    ServiceUnavailable      = 503,
    GatewayTimeout          = 504,
    HttpVersionNotSupported = 505
};

class HttpStatusCodeHelper
{
public:
    static std::string_view getHttpStatusDescription(HttpStatusCode code);

private:
    static constexpr size_t                                                                   NumberOfStatusCodes = 23;
    static const std::array<std::pair<HttpStatusCode, std::string_view>, NumberOfStatusCodes> StatusCodeArray;
};

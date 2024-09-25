#include "HttpStatusCode.hpp"

#include "SocketException.hpp"

std::string_view HttpStatusHelper::getHttpStatusDescription(HttpStatusCode code)
{
    auto it = m_status_code_map.find(code);
    if (it == m_status_code_map.end())
    {
        throw SocketException("HttpStatusCode: Undefined status code");
    }
    return it->second;
}

const std::map<HttpStatusCode, std::string_view> HttpStatusHelper::m_status_code_map = {
    {HttpStatusCode::OK, "200 OK"},
    {HttpStatusCode::Created, "201 Created"},
    {HttpStatusCode::NoContent, "204 No Content"},
    {HttpStatusCode::MovedPermanently, "301 Moved Permanently"},
    {HttpStatusCode::Found, "302 Found"},
    {HttpStatusCode::NotModified, "304 Not Modified"},
    {HttpStatusCode::BadRequest, "400 Bad Request"},
    {HttpStatusCode::Unauthorized, "401 Unauthorized"},
    {HttpStatusCode::Forbidden, "403 Forbidden"},
    {HttpStatusCode::NotFound, "404 Not Found"},
    {HttpStatusCode::MethodNotAllowed, "405 Method Not Allowed"},
    {HttpStatusCode::RequestTimeout, "408 Request Timeout"},
    {HttpStatusCode::Conflict, "409 Conflict"},
    {HttpStatusCode::Gone, "410 Gone"},
    {HttpStatusCode::PayloadTooLarge, "413 Payload Too Large"},
    {HttpStatusCode::UnsupportedMediaType, "415 Unsupported Media Type"},
    {HttpStatusCode::TooManyRequests, "429 Too Many Requests"},
    {HttpStatusCode::InternalServerError, "500 Internal Server Error"},
    {HttpStatusCode::NotImplemented, "501 Not Implemented"},
    {HttpStatusCode::BadGateway, "502 Bad Gateway"},
    {HttpStatusCode::ServiceUnavailable, "503 Service Unavailable"},
    {HttpStatusCode::GatewayTimeout, "504 Gateway Timeout"}};

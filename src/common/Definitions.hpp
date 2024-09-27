#pragma once

#include <string>
#include <unordered_map>

using HttpHeaders = std::unordered_map<std::string_view, std::string_view>;

static constexpr std::string_view HttpVersion = "HTTP/1.1";

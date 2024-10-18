#pragma once

#include <string>
#include <unordered_map>

static constexpr int BufferSize = 4096;

using HttpHeaders = std::unordered_map<std::string, std::string>;

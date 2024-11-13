#pragma once

#include <optional>
#include <string>
#include <unordered_map>

static constexpr int BufferSize = 1024;

using HttpHeaders = std::unordered_map<std::string, std::string>;

using OptionalErrorMessage = std::optional<std::string>;

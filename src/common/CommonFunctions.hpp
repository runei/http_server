#pragma once

#include <filesystem>
#include <string>

class CommonFunctions
{
public:
    static std::string getStaticFolderPath() { return {STATIC_DIR_PATH}; }
};

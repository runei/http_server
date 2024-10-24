#pragma once

#include <fstream>
#include <memory>
#include <mutex>
#include <string>

class Logger
{
public:
    Logger(const Logger&)            = delete;
    Logger& operator=(const Logger&) = delete;
    Logger(Logger&&)                 = delete;
    Logger operator=(Logger&&)       = delete;

    virtual ~Logger();

    static Logger& getInstance();
    static void    destroyInstance(); // Made for testing

    void log(const std::string& message, const std::string& level);
    void logInfo(const std::string& message);
    void logSuccess(const std::string& message);
    void logError(const std::string& message);

protected:
    Logger();

    virtual void writeToFile(const std::string& message);

private:
    std::ofstream m_log_file;
};

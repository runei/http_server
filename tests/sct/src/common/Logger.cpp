#include "Logger.hpp"

#include <iostream>
#include <string>

Logger::Logger()
{
    m_log_file.open("log.txt");
    if (!m_log_file.is_open())
    {
        std::cerr << "Logger: Error opening log file!" << "\n";
    }
}

Logger::~Logger()
{
    close();
}

Logger& Logger::getInstance()
{
    static Logger instance;
    return instance;
}

void Logger::log(const std::string& message, const std::string& level)
{
    const std::string log_entry = "[" + level + "] " + message;
    std::cout << log_entry << "\n";
    writeToFile(log_entry);
}

void Logger::logInfo(const std::string& message)
{
    log(message, "INFO");
}

void Logger::logSuccess(const std::string& message)
{
    log(message, "SUCCESS");
}

void Logger::logError(const std::string& message)
{
    log(message, "ERROR");
}

void Logger::disableFileOutput()
{
    close();
}

void Logger::close()
{
    if (m_log_file.is_open())
    {
        m_log_file.close();
    }
}

void Logger::writeToFile(const std::string& message)
{
    if (m_log_file.is_open())
    {
        m_log_file << message << "\n";
    }
}

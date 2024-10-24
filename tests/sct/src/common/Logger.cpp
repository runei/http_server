#include "Logger.hpp"

#include <iostream>

Logger::Logger()
{
    m_log_file.open("log.txt");
    if (!m_log_file.is_open())
    {
        std::cerr << "Logger: Error opening log file!" << std::endl;
    }
}

Logger::~Logger()
{
    if (m_log_file.is_open())
    {
        m_log_file.close();
    }
}

Logger& Logger::getInstance()
{
    static Logger instance;
    return instance;
}

void Logger::log(const std::string& message, const std::string& level)
{
    std::string log_entry = "[" + level + "] " + message;
    std::cout << log_entry << std::endl;
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

void Logger::writeToFile(const std::string& message)
{
    if (m_log_file.is_open())
    {
        m_log_file << message << std::endl;
    }
}

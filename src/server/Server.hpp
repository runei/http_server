#pragma once

#include <condition_variable>
#include <mutex>

#include "RequestDispatcher.hpp"

class Server
{
public:
    explicit Server(uint16_t port);
    ~Server();

    Server(const Server&)            = delete;
    Server& operator=(const Server&) = delete;
    Server(Server&&)                 = delete;
    Server& operator=(Server&&)      = delete;

    void start();
    void stop();
    void waitForServerToStart();

private:
    void               setupSocket() const;
    void               listenForConnections();
    void               updateServerRunningState(bool is_running);
    [[nodiscard]] bool isServerRunning() const;

    uint16_t                m_port;
    RequestDispatcher       m_dispatcher;
    std::atomic<bool>       m_is_running{false};
    std::mutex              m_mutex;
    std::condition_variable m_condition;

    static constexpr uint8_t MaxNumberOfConnections = 10;
};

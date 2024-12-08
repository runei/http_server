#pragma once

#include <cstdint>
#include <memory>
#include <thread>

#include "Definitions.hpp"
#include "Server.hpp"
#include "TestCase.hpp"

class ServerTestCase : public TestCase
{
public:
    explicit ServerTestCase(uint16_t port);
    ~ServerTestCase() override = default;

protected:
    OptionalErrorMessage setup() override;
    OptionalErrorMessage teardown() override;

    OptionalErrorMessage execute() final;

    virtual OptionalErrorMessage executeServerTest() = 0;

private:
    uint16_t                m_port;
    std::unique_ptr<Server> m_server;
    std::thread             m_server_thread;
};

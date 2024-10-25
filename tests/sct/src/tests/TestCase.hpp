#pragma once

class TestCase
{
public:
    TestCase(const TestCase&)            = delete;
    TestCase& operator=(const TestCase&) = delete;
    TestCase(TestCase&&)                 = delete;
    TestCase& operator=(TestCase&&)      = delete;

    virtual ~TestCase() = default;

    void run()
    {
        setup();
        execute();
        tearDown();
    }

protected:
    virtual void setup()   = 0;
    virtual void execute() = 0;
    virtual void tearDown() {};
};

#include <CppUTest/TestHarness.h> // NOLINT(misc-include-cleaner)

#include <CppUTest/UtestMacros.h>

#include <memory>

#include "Logger.hpp"
#include "MockTestCase.hpp"
#include "TestCaseResult.hpp"

TEST_GROUP (TestCaseTest)
{
    void setup() override
    {
        Logger::getInstance().disableFileOutput();
        m_test_case = std::make_unique<MockTestCase>();
    }

    std::unique_ptr<MockTestCase>& getTestCase()
    {
        return m_test_case;
    }

private:
    std::unique_ptr<MockTestCase> m_test_case;
};

TEST (TestCaseTest, SuccessfulExecution)
{
    // Arrange
    getTestCase()->setSetupResult(true, "");
    getTestCase()->setExecuteResult(true, "");
    getTestCase()->setTeardownResult(true, "");

    // Act
    getTestCase()->run();

    // Assert
    CHECK_TRUE(getTestCase()->wasSetupCalled());
    CHECK_TRUE(getTestCase()->wasExecuteCalled());
    CHECK_TRUE(getTestCase()->wasTeardownCalled());

    const TestCaseResult& test_result = getTestCase()->getResult();
    CHECK_TRUE(test_result.isSuccess());
    STRCMP_EQUAL("", test_result.getMessage().c_str());
}

TEST (TestCaseTest, SetupFails)
{
    // Arrange
    getTestCase()->setSetupResult(false, "Setup failed");

    // Act
    getTestCase()->run();

    // Asserts
    CHECK_TRUE(getTestCase()->wasSetupCalled());
    CHECK_FALSE(getTestCase()->wasExecuteCalled());
    CHECK_TRUE(getTestCase()->wasTeardownCalled());

    const TestCaseResult& test_result = getTestCase()->getResult();
    CHECK_FALSE(test_result.isSuccess());
    STRCMP_EQUAL("Setup Failed: Setup failed", test_result.getMessage().c_str());
}

TEST (TestCaseTest, ExecuteFails)
{
    // Arrange
    getTestCase()->setSetupResult(true, "");
    getTestCase()->setExecuteResult(false, "Execution failed");

    // Act
    getTestCase()->run();

    // Assert
    CHECK_TRUE(getTestCase()->wasSetupCalled());
    CHECK_TRUE(getTestCase()->wasExecuteCalled());
    CHECK_TRUE(getTestCase()->wasTeardownCalled());

    const TestCaseResult& test_result = getTestCase()->getResult();
    CHECK_FALSE(test_result.isSuccess());
    STRCMP_EQUAL("Execution Failed: Execution failed", test_result.getMessage().c_str());
}

TEST (TestCaseTest, TeardownFails_ResultSuccsess)
{
    // Arrange
    getTestCase()->setSetupResult(true, "");
    getTestCase()->setExecuteResult(true, "");
    getTestCase()->setTeardownResult(false, "Teardown failed");

    // Act
    getTestCase()->run();

    // Assert
    CHECK_TRUE(getTestCase()->wasSetupCalled());
    CHECK_TRUE(getTestCase()->wasExecuteCalled());
    CHECK_TRUE(getTestCase()->wasTeardownCalled());

    const TestCaseResult& test_result = getTestCase()->getResult();
    CHECK_TRUE(test_result.isSuccess());
    STRCMP_EQUAL("", test_result.getMessage().c_str());
}

TEST (TestCaseTest, GetResult_BeforeRun_ReturnDefaultResult)
{
    // Arrange & Act
    const TestCaseResult& test_result = getTestCase()->getResult();

    // Assert
    CHECK_FALSE(test_result.isSuccess());
    STRCMP_EQUAL("", test_result.getMessage().c_str());
}

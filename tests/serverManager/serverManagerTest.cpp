#include "serverManager.hpp"
#include "mu_test.h"
#include <climits>
#include <iostream>
#include <iomanip>

BEGIN_TEST(create_server_manager)
    kofiko::ServerManager serverManager("127.0.0.1", 1234, 5);
    ASSERT_PASS();
END_TEST

BEGIN_TEST(server_manager_run)
    kofiko::ServerManager serverManager("127.0.0.1", 1234, 5);
    serverManager.RunServer();
    ASSERT_PASS();
END_TEST

BEGIN_SUITE(test)
    TEST(create_server_manager)
    TEST(server_manager_run)
END_SUITE
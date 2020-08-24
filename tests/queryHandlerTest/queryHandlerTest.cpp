#include "queryHandler.hpp"
#include "dataFunc.hpp"
#include "mu_test.h"
#include <climits>
#include <iostream>
#include <iomanip>
using namespace std;
using namespace data;
using namespace kokfikoCDR;

BEGIN_TEST(create_query_handler)
    CustomerBilling customerBilling(5);
    OperatorBilling operatorBilling(5);
    QueryHandler dataHandler(&customerBilling, &operatorBilling);
    ASSERT_PASS();
END_TEST

BEGIN_TEST(query_request)
    vector<string> values;
    FillValues(values);
    CdrRecord record(values);

    CustomerBilling customerBilling(5);
    OperatorBilling operatorBilling(5);
    QueryHandler dataHandler(&customerBilling, &operatorBilling);
    customerBilling.Update(record);
    operatorBilling.Update(record);

    Customer customer;
    dataHandler.GetCustomerQuery("9720528409042", customer);
    Operator mobileOp;
    dataHandler.GetOperatorQuery("42502", mobileOp);

    ASSERT_THAT(CheckResult(customer, mobileOp));
END_TEST

BEGIN_SUITE(test)
    TEST(create_query_handler)
    TEST(query_request)
END_SUITE
#include "dataAggregatorHandler.hpp"
#include "dataFunc.hpp"
#include "mu_test.h"
#include <climits>
#include <iostream>
#include <iomanip>
using namespace std;
using namespace data;
using namespace kofiko;

BEGIN_TEST(create_data_aggregator_handler)
    CustomerBilling customerBilling(5);
    OperatorBilling operatorBilling(5);
    DataAggregatorHandler dataHandler(&customerBilling, &operatorBilling);
    ASSERT_PASS();
END_TEST

BEGIN_TEST(update_record)
    vector<string> values;
    FillValues(values);
    CdrRecord record(values);

    CustomerBilling customerBilling(5);
    OperatorBilling operatorBilling(5);
    DataAggregatorHandler dataHandler(&customerBilling, &operatorBilling);
    dataHandler.InsertNewRecord(record);

    Customer customer;
    customerBilling.Query("9720528409042", customer);
    Operator mobileOp;
    operatorBilling.Query("42502", mobileOp);

    ASSERT_THAT(CheckResult(customer, mobileOp));
END_TEST

BEGIN_SUITE(test)
    TEST(create_data_aggregator_handler)
    TEST(update_record)
END_SUITE
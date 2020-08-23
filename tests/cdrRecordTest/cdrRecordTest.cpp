#include "cdrRecord.hpp"
#include "testFunc.hpp"
#include <sstream>
#include <string>
#include <iostream>
using namespace kokfikoCDR;
using namespace std;

static void TestRecord(vector<string>& a_values) {
    kokfikoCDR::CdrRecord record(a_values);
    static int testNum = 0;
    PrintResult("record create", CheckRecord(record, a_values), testNum, ": \t");
}

int main() {
    vector<string> values;
    FillValues(values);
    TestRecord(values);

    return 0;
}
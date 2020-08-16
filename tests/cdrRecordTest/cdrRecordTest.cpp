#include "cdrRecord.hpp"
#include "testFunc.hpp"
#include <sstream>
#include <string>
#include <iostream>
using namespace std;

typedef kokfikoCDR::CdrRecord::RecordInfo RecordInfo;

namespace kokfikoCDR {

static void TestRecord(RecordInfo& a_values) {
    kokfikoCDR::CdrRecord record(a_values);
    static int testNum = 0;
    PrintResult("record create", CheckRecord(record, a_values), testNum, ": \t");
}

} // kokfikoCDR

int main() {
    kokfikoCDR::CdrRecord::RecordInfo values;
    kokfikoCDR::FillValues(values);
    kokfikoCDR::TestRecord(values);

    return 0;
}
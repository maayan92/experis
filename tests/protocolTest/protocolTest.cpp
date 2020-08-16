#include "protocol.hpp"
#include "testFunc.hpp"
#include <iostream>
using namespace std;
using namespace kokfikoCDR;

#define BUFFER_SIZE 200

typedef kokfikoCDR::CdrRecord::RecordInfo Record;

namespace tcp {

static bool CheckNext(char* a_buffer, Record& a_values, size_t& a_bufPos, size_t& a_valuesPos) {
    size_t valSize = a_values[a_valuesPos].size();
    bool result = (valSize == a_buffer[a_bufPos++]) && (0 == strncmp(a_buffer + a_bufPos, a_values[a_valuesPos].c_str(), valSize));
    a_bufPos += valSize;
    ++a_valuesPos;
    return result;
}

static bool CheckResult(char* a_buffer, Record& a_values) {
    size_t bufPos = 0, valuesPos = 0, valSize = a_values[valuesPos].size();
    bool result = (100 == a_buffer[bufPos++]);

    while(valuesPos < a_values.size()) {
        result = result && CheckNext(a_buffer, a_values, bufPos, valuesPos);
    }
    
    return result;
}

static void TestProtocolPackMsg() {
    Record values;
    FillValues(values);
    CdrRecord record(values);
    char buffer[BUFFER_SIZE];
    static int testNum = 0;

    try {
        Protocol::PackMessage(record, buffer, BUFFER_SIZE);
        bool result = CheckResult(buffer, values);

        PrintResult("protocol pack message", result, testNum);
    }catch(const exception& exc) {
        cout << exc.what() << endl;
        PrintResult("protocol pack message", false, testNum);
    }
}

} // tcp

int main() {
    tcp::TestProtocolPackMsg();

    return 0;
}
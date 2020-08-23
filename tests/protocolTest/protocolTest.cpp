#include "protocol.hpp"
#include <iostream>
using namespace std;
using namespace kokfikoCDR;

#define BUFFER_SIZE 200

static void FillValues(vector<string>& a_values);
static bool CheckRecord(const CdrRecord& a_record, const vector<string>& a_values);
static bool CompareRecords(const CdrRecord& a_left, const CdrRecord& a_right);
static void PrintResult(const char* a_test, bool a_result, int& a_testNum, const char* a_tabs);

namespace tcp {

static bool CheckNext(char* a_buffer, const vector<string>& a_values, size_t& a_bufPos, size_t& a_valuesPos) {
    size_t valSize = a_values[a_valuesPos].size();
    size_t size = a_buffer[a_bufPos++];
    bool result = (valSize == size) && (0 == strncmp(a_buffer + a_bufPos, a_values[a_valuesPos].c_str(), valSize));
    a_bufPos += valSize;
    ++a_valuesPos;
    return result;
}

static bool CheckResult(char* a_buffer, const vector<string>& a_values) {
    size_t bufPos = 0;
    size_t valuesPos = 0;
    bool result = (100 == a_buffer[bufPos++]);

    while(valuesPos < a_values.size()) {
        result = result && CheckNext(a_buffer, a_values, bufPos, valuesPos);
    }
    
    return result;
}

static void TestProtocolPackMsg(const CdrRecord& a_record, const vector<string>& a_values) {
    char buffer[BUFFER_SIZE];
    static int testNum = 0;

    try {
        Protocol::PackMessage(a_record, buffer, BUFFER_SIZE);
        bool result = CheckResult(buffer, a_values);

        PrintResult("protocol pack message", result, testNum, ": \t\t");
    }catch(const exception& exc) {
        cout << exc.what() << endl;
        PrintResult("protocol pack message", false, testNum, ": \t\t");
    }
}

static void TestProtocolUnPackMsg(const CdrRecord& a_record) {
    char buffer[BUFFER_SIZE];
    static int testNum = 0;

    try {
        Protocol::PackMessage(a_record, buffer, BUFFER_SIZE);
        Protocol::Record recordResult = Protocol::UnPackMessage(buffer);
        bool result = CompareRecords(a_record, recordResult);

        PrintResult("protocol unpack message", result, testNum, ": \t");
    }catch(const exception& exc) {
        cout << exc.what() << endl;
        PrintResult("protocol unpack message", false, testNum, ": \t");
    }
}

} // tcp

int main() {
    vector<string> values;
    FillValues(values);
    CdrRecord record(values);
    tcp::TestProtocolPackMsg(record, values);
    tcp::TestProtocolUnPackMsg(record);

    return 0;
}
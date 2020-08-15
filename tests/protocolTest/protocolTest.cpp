#include "protocol.hpp"
#include <iostream>

#define BUFFER_SIZE 200

typedef kokfikoCDR::CdrRecord::RecordInfo Record;

namespace tcp {

static void FillVector(Record& a_values) {
    a_values.push_back("123");
    a_values.push_back("425020528409010"); // 15
    a_values.push_back("35-209900-176148-1"); // 18
    a_values.push_back("MOC");
    a_values.push_back("9720528409042"); // 13
    a_values.push_back("DD/MM/YYYY"); // 10
    a_values.push_back("HH:MM:SS"); // 8
    a_values.push_back("2152");
    a_values.push_back("64");
    a_values.push_back("32");
    a_values.push_back("61523827346"); // 11
}

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
    FillVector(values);
    kokfikoCDR::CdrRecord record(values);
    char buffer[BUFFER_SIZE];
    Protocol::PackMessage(record, buffer, BUFFER_SIZE);

    bool result = CheckResult(buffer, values);

    static int testNum = 0;
    std::cout << "protocol pack message, test number " <<  ++testNum << ": \t"
            << (result ? "\033[1;31mSUCCESS" : "\033[1;32mFAILED")
                << "\033[0m" << std::endl;
}

} // tcp

int main() {
    tcp::TestProtocolPackMsg();

    return 0;
}
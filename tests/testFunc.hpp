#include "cdrRecord.hpp"
#include <iostream>
using namespace std;

namespace kokfikoCDR {

static void FillValues(CdrRecord::RecordInfo& a_values) {
    a_values.push_back("123");
    a_values.push_back("425020528409010");
    a_values.push_back("35-209900-176148-1");
    a_values.push_back("MOC");
    a_values.push_back("9720528409042");
    a_values.push_back("DD/MM/YYYY");
    a_values.push_back("HH:MM:SS");
    a_values.push_back("2152");
    a_values.push_back("64");
    a_values.push_back("32");
    a_values.push_back("61523827346");
}

static void PrintResult(const char* a_test, bool a_result, int& a_testNum) {
    cout << a_test << ", test number " <<  ++a_testNum << ": \t"
            << (a_result ? "\033[1;31mSUCCESS" : "\033[1;32mFAILED")
                << "\033[0m" << endl;
}

} // kokfikoCDR
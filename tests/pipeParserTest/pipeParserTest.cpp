#include "pipeParser.hpp"
#include "testFunc.hpp"
#include <iostream>
using namespace std;

namespace kofiko {

static void TestParsing(const std::string& a_info, const CdrRecord& a_values) {
    static int testNum = 0;
    PipeParser pipeParser;
    CdrRecord result = pipeParser.Parsering(a_info);
    
    PrintResult("parsing", CompareRecords(result, a_values), testNum, ": \t");
}

} // kofiko

int main() {
    std::string buffer("123|425020528409010|35-209900-176148-1|MOC|9720528409042|DD/MM/YYYY|HH:MM:SS|2152|64|32|61523827346");
    vector<string> a_values;
    kofiko::FillValues(a_values);
    
    kofiko::CdrRecord result(a_values);

    kofiko::TestParsing(buffer, result);
    buffer += '|';
    kofiko::TestParsing(buffer, result);

    return 0;
}
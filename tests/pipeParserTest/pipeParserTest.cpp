#include "pipeParser.hpp"
#include "testFunc.hpp"
#include <iostream>
using namespace std;

namespace kokfikoCDR {

static void TestParsing(const std::string& a_info, const CdrRecord& a_values) {
    static int testNum = 0;
    PipeParser pipeParser;
    CdrRecord result = pipeParser.Parsering(a_info);
    
    PrintResult("parsing", CompareRecords(result, a_values), testNum, ": \t");
}

} // kokfikoCDR

int main() {
    std::string buffer("123|425020528409010|35-209900-176148-1|MOC|9720528409042|DD/MM/YYYY|HH:MM:SS|2152|64|32|61523827346");
    vector<string> a_values;
    kokfikoCDR::FillValues(a_values);
    
    kokfikoCDR::CdrRecord result(a_values);

    kokfikoCDR::TestParsing(buffer, result);
    buffer += '|';
    kokfikoCDR::TestParsing(buffer, result);

    return 0;
}
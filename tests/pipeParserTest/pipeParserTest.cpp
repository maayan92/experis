#include "pipeParser.hpp"
#include <iostream>

namespace kokfikoCDR {

static void TestParsing(std::string a_info, IParser::RecordInfo a_wantedResult) {
    static int testNum = 0;
    PipeParser pipeParser;
    IParser::RecordInfo result = pipeParser.Parsering(a_info);
    
    std::cout << "parsing, test number " <<  ++testNum << ": \t"
            << ((result == a_wantedResult) ? "\033[1;31mSUCCESS" : "\033[1;32mFAILED") 
                << "\033[0m" << std::endl;
}

} // kokfikoCDR

int main() {
    std::string buffer("​9720528409042|61523|outgoing voice call|DD/MM/YYYY");
    kokfikoCDR::IParser::RecordInfo wantedResult;
    wantedResult.push_back("​9720528409042");
    wantedResult.push_back("61523");
    wantedResult.push_back("outgoing voice call");
    wantedResult.push_back("DD/MM/YYYY");

    kokfikoCDR::TestParsing(buffer, wantedResult);
    buffer += '|';
    kokfikoCDR::TestParsing(buffer, wantedResult);

    return 0;
}
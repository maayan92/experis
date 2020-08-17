#include "pipeParser.hpp"
#include <iostream>
using namespace std;

namespace kokfikoCDR {

CdrRecord PipeParser::Parsering(const string& a_buffer) {
    size_t fromPos = 0, toPos = a_buffer.find(delimiter);
    RecordInfo info;

    while(toPos != string::npos) {
        string token(a_buffer,fromPos , toPos - fromPos);
        if(token.size() > 0) {
            info.push_back(token);
        }

        fromPos = toPos + 1;
        toPos = a_buffer.find(delimiter, fromPos);
    }
    if(fromPos < a_buffer.size()) {
        string token(a_buffer,fromPos , a_buffer.size() - fromPos);
        info.push_back(token);
    }

    return CdrRecord(info);
}

} // kokfikoCDR
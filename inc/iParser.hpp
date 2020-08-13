#ifndef IPARSER_H
#define IPARSER_H

#include <string>
#include <vector>
#include "cdrRecord.hpp"

namespace kokfikoCDR {

class IParser {
public:
    typedef std::string String;
    typedef std::vector<String> RecordInfo;

    //IParser() = default;
    //IParser(const IParser& a_iparser) = default;
    virtual ~IParser() {}

    virtual CdrRecord Parsering(String a_buffer) = 0;
};

} // kokfikoCDR

#endif
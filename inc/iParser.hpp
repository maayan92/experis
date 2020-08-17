#ifndef IPARSER_H
#define IPARSER_H

#include <string>
#include <vector>
#include "cdrRecord.hpp"

namespace kokfikoCDR {

class IParser {
public:
    //IParser() = default;
    //IParser(const IParser& a_iparser) = default;
    virtual ~IParser();

    virtual CdrRecord Parsering(const std::string& a_buffer) = 0;
};

} // kokfikoCDR

#endif
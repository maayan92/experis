#ifndef __IPARSER_H__
#define __IPARSER_H__

#include <string>
#include <vector>

namespace kokfikoCDR {

class IParser {
public:
    typedef std::string String;
    typedef std::vector<String> RecordInfo;

    //IParser() = default;
    //IParser(const IParser& a_iparser) = default;
    virtual ~IParser();

    virtual RecordInfo Parsering(String a_buffer) = 0;
};

} // kokfikoCDR

#endif
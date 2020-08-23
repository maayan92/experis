#ifndef IPARSER_H
#define IPARSER_H

#include "cdrRecord.hpp"
#include "uncopyable.hpp"
#include <string>
#include <vector>

namespace kokfikoCDR {

class IParser : private experis::Uncopyable{
public:
    virtual ~IParser();

    virtual CdrRecord Parsering(const std::string& a_buffer) = 0;

protected:
    IParser();
};

} // kokfikoCDR

#endif
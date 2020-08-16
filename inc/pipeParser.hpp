#ifndef PIPE_PARSER_H
#define PIPE_PARSER_H

#include "iParser.hpp"

namespace kokfikoCDR {

class PipeParser : public IParser {
public:
    //PipeParser() = default;
    //PipeParser(const PipeParser& a_pipeParser) = default;
    virtual ~PipeParser() {}
    //PipeParser& operator(const PipeParser& a_pipeParser) = default;

    virtual CdrRecord Parsering(const String& a_buffer);

private:
    static const char delimiter = '|';
};

} // kokfikoCDR

#endif
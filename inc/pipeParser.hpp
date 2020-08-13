#ifndef __PIPE_PARSER_H__
#define __PIPE_PARSER_H__

#include "iParser.hpp"

namespace kokfikoCDR {

class PipeParser : public IParser {
public:
    //PipeParser() = default;
    //PipeParser(const PipeParser& a_pipeParser) = default;
    //~PipeParser() = default;
    //PipeParser& operator(const PipeParser& a_pipeParser) = default;

    virtual RecordInfo Parsering(String a_buffer);

private:
    static const char delimiter = '|';
};

} // kokfikoCDR

#endif
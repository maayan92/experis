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

    virtual CdrRecord Parsering(const std::string& a_buffer);

private:
    void initializeInfo(std::vector<std::string>& a_info, const std::string& a_buffer);

private:
    static const size_t NUM_OF_RECORD_FIELDS = 11;
    static const int LUT[NUM_OF_RECORD_FIELDS];
    static const char delimiter = '|';
};

} // kokfikoCDR

#endif
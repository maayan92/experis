#ifndef PIPE_PARSER_H
#define PIPE_PARSER_H

#include "iParser.hpp"

namespace kokfikoCDR {

class PipeParser : public IParser {
public:
    //PipeParser() = default;
    //PipeParser(const PipeParser& a_pipeParser) = default;
    virtual ~PipeParser();
    //PipeParser& operator(const PipeParser& a_pipeParser) = default;

    virtual CdrRecord Parsering(const std::string& a_buffer);

private:
    void initializeInfo(std::vector<std::string>& a_info, const std::string& a_buffer);

private:
    static const int LUT[CdrRecord::NUM_OF_RECORD_FIELDS];
    static const char delimiter = '|';
};

} // kokfikoCDR

#endif
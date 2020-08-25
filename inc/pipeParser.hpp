#ifndef PIPE_PARSER_H
#define PIPE_PARSER_H

#include "iParser.hpp"

namespace kokfikoCDR {

class PipeParser : public IParser {
public:
    //PipeParser() = default;
    virtual ~PipeParser();

    virtual CdrRecord Parsering(const std::string& a_buffer);

private:
    void initializeInfo(std::vector<std::string>& a_info, const std::string& a_buffer);
    static void fillTheRest(std::vector<std::string>& a_info, const std::string& a_buffer, size_t a_fromPos, size_t a_pos);
    static bool isNotValidationValue(std::vector<std::string>& a_info);

private:
    static const int LUT[CdrRecord::NUM_OF_RECORD_FIELDS];
    static const char delimiter = '|';
};

} // kokfikoCDR

#endif
#ifndef PARSER_HPP
#define PARSER_HPP

#include "iParser.hpp"

namespace smart_house {

class Parser : public IParser {
public:
    //Parser() = default;
    //~Parser() = default;
    //Parser(const Parser& a_parser) = default;
    //Parser& operator=(const Parser& a_parser) = default;

    virtual void Parse(std::string& a_values, Device& a_device);

};

} // smart_house

#endif
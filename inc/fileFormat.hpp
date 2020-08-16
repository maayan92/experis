#ifndef FILE_FORMAT_H
#define FILE_FORMAT_H

#include "iParser.hpp"
#include "pipeParser.hpp"

namespace files {

class FileFormat {
public:
    static const size_t BUFFER_SIZE = 200;

    static kokfikoCDR::IParser* GetParser(std::istream& a_file);

private:
    ~FileFormat() {}
};

kokfikoCDR::IParser* FileFormat::GetParser(std::istream& a_file) {
    char buffer[BUFFER_SIZE];
    a_file.getline(buffer, BUFFER_SIZE);
    return new kokfikoCDR::PipeParser();
}

} // files

#endif
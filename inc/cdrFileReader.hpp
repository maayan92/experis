#ifndef CDR_FILE_READER_H
#define CDR_FILE_READER_H

#include <string>

namespace kokfikoCDR {

class CdrFileReader {
public:
    //CdrFileReader() = default;
    //CdrFileReader(const CdrFileReader& a_cdrFileReader) = default;
    //~CdrFileReader() = default;
    //CdrFileReader& operator=(const CdrFileReader& a_cdrFileReader) = default;

    void ReadFile(std::string& a_filename);
};

} // kokfikoCDR

#endif
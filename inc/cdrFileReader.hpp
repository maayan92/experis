#ifndef CDR_FILE_READER_H
#define CDR_FILE_READER_H

#include "cdrSender.hpp"
#include <fstream>
#include <iostream>

namespace kokfikoCDR {

class CdrFileReader {
public:
    CdrFileReader();
    //CdrFileReader(const CdrFileReader& a_cdrFileReader) = default;
    //~CdrFileReader() = default;
    //CdrFileReader& operator=(const CdrFileReader& a_cdrFileReader) = default;

    void ReadFile(std::istream& a_file);

private:
    CdrSender m_sender;
};

} // kokfikoCDR

#endif
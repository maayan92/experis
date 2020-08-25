#ifndef CDR_FILE_READER_H
#define CDR_FILE_READER_H

#include "cdrSender.hpp"
#include "uncopyable.hpp"
#include <fstream>
#include <iostream>

namespace kofiko {

class CdrFileReader : private experis::Uncopyable {
public:
    CdrFileReader(const char* a_ipAddress, size_t a_port);
    //~CdrFileReader() = default;

    void ReadFile(std::istream& a_file);

private:
    CdrSender m_sender;
};

} // kofiko

#endif
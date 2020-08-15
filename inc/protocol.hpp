#ifndef PROTOCOL_H
#define PROTOCOL_H

#include "cdrRecord.hpp"

namespace tcp {

class Protocol {
public:
    typedef kokfikoCDR::CdrRecord Record;
    static const size_t NUM_OF_RECORDS = 11;
    
    static void PackMessage(const Record& a_record, char* a_buffer, size_t a_bufferSize);
    static Record UnPackMessage(const char* a_msg);

private:
    ~Protocol() {}
};

} // tcp

#endif
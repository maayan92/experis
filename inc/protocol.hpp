#ifndef PROTOCOL_H
#define PROTOCOL_H

#include "cdrRecord.hpp"

namespace tcp {

class Protocol {
public:
    static const size_t NUM_OF_RECORDS = 11;
    
    static void PackMessage(const kofiko::CdrRecord& a_record, char* a_buffer, size_t a_bufferSize);
    static kofiko::CdrRecord UnPackMessage(const char* a_msg);

private:
    ~Protocol() {}
};

} // tcp

#endif
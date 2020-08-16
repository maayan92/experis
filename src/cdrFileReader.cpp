#include  "cdrFileReader.hpp"
#include "fileFormat.hpp"
#include "exceptions.hpp"
using namespace std;
using namespace files;
using namespace exceptions;

namespace kokfikoCDR {

CdrFileReader::CdrFileReader() 
: m_sender()
{
}

void CdrFileReader::ReadFile(istream& a_file) {
    IParser* parser = FileFormat::GetParser(a_file);
    char buffer[FileFormat::BUFFER_SIZE];
    
    while(a_file.getline(buffer, FileFormat::BUFFER_SIZE)) {
        CdrRecord record = parser->Parsering(buffer);
        m_sender.SendMessage(record);
    }
}

} // kokfikoCDR
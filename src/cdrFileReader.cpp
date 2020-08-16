#include  "cdrFileReader.hpp"
#include "fileFormat.hpp"
#include "exceptions.hpp"
#include "cdrSender.hpp"
#include "pipeParser.hpp" // temporary
using namespace std;
using namespace files;
using namespace exceptions;

namespace kokfikoCDR {

static const size_t BUFFER_SIZE = 200;

static void ReadFromFile(ifstream& file, IParser* a_parser) {
    char buffer[BUFFER_SIZE];
    file.getline(buffer, BUFFER_SIZE); // temporary
    CdrSender sender;
    
    while(file.getline(buffer, BUFFER_SIZE)) {
        CdrRecord record = a_parser->Parsering(buffer);
        sender.SendMessage(record);
    }
}

void CdrFileReader::ReadFile(const string& a_filename) {
    ifstream file(a_filename.c_str());
    if(file.fail()) {
        throw ExcFileFailedToOpen();
    }
    //IParser* parser = FileFormat::GetParser(file);
    IParser* parser = new PipeParser();
    ReadFromFile(file, parser);
}

} // kokfikoCDR
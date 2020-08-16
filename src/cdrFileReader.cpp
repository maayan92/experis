#include  "cdrFileReader.hpp"
#include "fileFormat.hpp"
#include "exceptions.hpp"
#include "pipeParser.hpp" // temporary
using namespace std;
using namespace files;
using namespace exceptions;

namespace kokfikoCDR {

static const size_t BUFFER_SIZE = 200;

void CdrFileReader::ReadFile(const string& a_filename) {
    ifstream file(a_filename);
    if(file.fail()) {
        throw ExcFileFailedToOpen();
    }
    //IParser* parser = FileFormat::GetParser(file);
    IParser* parser = new PipeParser();
    char buffer[BUFFER_SIZE];

    file.getline(buffer, BUFFER_SIZE); // temporary
    while(file.getline(buffer, BUFFER_SIZE)) {

    }
}

} // kokfikoCDR
#include "cdrFileReader.hpp"
#include "testFunc.hpp"

namespace kokfikoCDR {

static void TestReadFile() {
    CdrFileReader readFile;
    static int testNum = 0;
    try {
        readFile.ReadFile("testFile.txt");
        PrintResult("read file", true, testNum);

    }catch(const exception& exc) {
        cout << exc.what() << endl;
        PrintResult("read file", false, testNum);
    }
}

} // kokfikoCDR

int main() {
    kokfikoCDR::TestReadFile();

    return 0;
}
#include "cdrFileReader.hpp"
#include "testFunc.hpp"
#include <iostream>
using namespace std;

namespace kokfikoCDR {

static void TestReadFile() {
    CdrFileReader readFile("127.0.0.1", 1234);
    static int testNum = 0;
    ifstream file("data.out");
    try {
        readFile.ReadFile(file);
        PrintResult("read file", true, testNum, ": \t");

    }catch(const exception& exc) {
        cout << exc.what() << endl;
        PrintResult("read file", false, testNum, ": \t");
    }
}

} // kokfikoCDR

int main() {
    kokfikoCDR::TestReadFile();

    return 0;
}
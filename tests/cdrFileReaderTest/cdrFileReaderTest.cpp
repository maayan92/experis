#include "cdrFileReader.hpp"
#include <iostream>
using namespace std;

namespace kokfikoCDR {

static void PrintResult(const char* a_test, bool a_result, int& a_testNum, const char* a_tabs) {
    cout << a_test << ", test number " <<  ++a_testNum << a_tabs
            << (a_result ? "\033[1;31mSUCCESS" : "\033[1;32mFAILED")
                << "\033[0m" << endl;
}

static void TestReadFile() {
    CdrFileReader readFile;
    static int testNum = 0;
    ifstream file("testFile.txt");
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
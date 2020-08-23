#include "cdrSender.hpp"
#include "testFunc.hpp"
#include <iostream>
using namespace std;

namespace kokfikoCDR {

static void TestSender() {
    static int testNum = 0;
    vector<string> a_values;
    FillValues(a_values);
    CdrRecord record(a_values);
    
    try {
        CdrSender sender("127.0.0.1", 1234);
        sender.SendMessage(record);
        PrintResult("sender", true, testNum, ": \t");

    }catch(const exception& exc) {
        cout << exc.what() << endl;
        PrintResult("sender", false, testNum, ": \t");
    }
}

} // kokfikoCDR

int main() {
    kokfikoCDR::TestSender();

    return 0;
}
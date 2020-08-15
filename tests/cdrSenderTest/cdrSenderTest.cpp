#include "cdrSender.hpp"
#include "testFunc.hpp"
#include <iostream>
using namespace std;

namespace kokfikoCDR {

static void TestSender() {
    static int testNum = 0;
    CdrRecord::RecordInfo a_values;
    FillValues(a_values);
    CdrRecord record(a_values);
    
    try {
        CdrSender sender;
        sender.SendMessage(record);
        PrintResult("sender", true, testNum);

    }catch(const exception& exc) {
        cout << exc.what() << endl;
        PrintResult("sender", false, testNum);
    }
}

} // kokfikoCDR

int main() {
    kokfikoCDR::TestSender();

    return 0;
}
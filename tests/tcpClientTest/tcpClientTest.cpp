#include "tcpClient.hpp"
#include "exceptions.hpp"
#include <iostream>
using namespace std;
using namespace kokfikoCDR;
using namespace exceptions;

static void PrintTestResult(const char* a_testName, int a_testNum, bool a_result) {
    cout << a_testName << ", test number " <<  ++a_testNum << ": \t"
            << (a_result ? "\033[1;31mSUCCESS" : "\033[1;32mFAILED")
                << "\033[0m" << endl;
}

static void TestCreateClient(const TcpClient& a_client) {
    static int testNum = 0;
    a_client.SendMessage("message from client");
    PrintTestResult("send data", testNum, true);
}

int main() {
    try {
        TcpClient client;
        PrintTestResult("create client", 0, true);
      
        TestCreateClient(client);

    }catch(const exception& exc) {
        cout << exc.what() << endl;
        PrintTestResult("create client or send data", 0, false);
    }

    return 0;
}
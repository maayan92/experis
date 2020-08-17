#include "tcpClient.hpp"
#include "exceptions.hpp"
#include <string.h>
#include <iostream>
using namespace std;
using namespace kokfikoCDR;
using namespace exceptions;

static const size_t BUFFER_SIZE = 200;

static void PrintResult(const char* a_test, bool a_result, int& a_testNum, const char* a_tabs) {
    cout << a_test << ", test number " <<  ++a_testNum << a_tabs
            << (a_result ? "\033[1;31mSUCCESS" : "\033[1;32mFAILED")
                << "\033[0m" << endl;
}

static void TestConnectToServer(TcpClient& a_client) {
    static int testNum = 0;
     try {
        a_client.ConnectToServer();
        PrintResult("connection", true, testNum, ": \t");

    }catch(const exception& exc) {
        cout << exc.what() << endl;
        PrintResult("connection", false, testNum, ": \t");
    }
}

static void TestSendData(TcpClient& a_client) {
    static int testNum = 0;
    try {
        a_client.SendMessage("message from client\n");
        PrintResult("send data", true, testNum, ": \t");

    }catch(const exception& exc) {
        cout << exc.what() << endl;
        PrintResult("send data", false, testNum, ": \t");
    }
}

static void TestRecieve(TcpClient& a_client) {
    static int testNum = 0;
    try {
        char buffer[BUFFER_SIZE];
        a_client.RecvMessage(a_client.GetSocketNumber(), buffer, BUFFER_SIZE);
        PrintResult("send data", (0 == strcmp(buffer, "message from client\n")), testNum, ": \t");

    }catch(const exception& exc) {
        cout << exc.what() << endl;
        PrintResult("send data", false, testNum, ": \t");
    }
}

int main() {
    static int testNum = 0;
    try {
        TcpClient client;
        PrintResult("create client", true, testNum, ": \t");
      
        TestConnectToServer(client);
        TestSendData(client);
        //TestRecieve(client);

    }catch(const exception& exc) {
        cout << exc.what() << endl;
        PrintResult("create client or send data", false, testNum, ": \t");
    }

    return 0;
}
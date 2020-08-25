#include "tcpClient.hpp"
#include "exceptions.hpp"
#include "testFunc.hpp"
#include <string.h>
#include <iostream>
#include <unistd.h>
using namespace std;
using namespace kofiko;
using namespace exceptions;

static const size_t BUFFER_SIZE = 200;

static void TestCreateClient() {
    static int testNum = 0;
    try {
        TcpClient client("127.0.0.1", 1234);
        PrintResult("create client", true, testNum, ": \t");

    }catch(const exception& exc) {
        cout << exc.what() << endl;
        PrintResult("create client", false, testNum, ": \t");
    }
}

static void TestConnectToServer() {
    static int testNum = 0;
    try {
        TcpClient client("127.0.0.1", 1234);
        client.ConnectToServer();
        PrintResult("connection", true, testNum, ": \t");

    }catch(const exception& exc) {
        cout << exc.what() << endl;
        PrintResult("connection", false, testNum, ": \t");
    }
}

static void TestSendData() {
    static int testNum = 0;
    try {
        TcpClient client("127.0.0.1", 1234);
        client.ConnectToServer();
        client.SendMessage("message from client\n");
        PrintResult("send data", true, testNum, ": \t");

    }catch(const exception& exc) {
        cout << exc.what() << endl;
        PrintResult("send data", false, testNum, ": \t");
    }
}

int main() {
    TestCreateClient();
    sleep(1);
    TestConnectToServer();
    sleep(1);
    TestSendData();

    return 0;
}
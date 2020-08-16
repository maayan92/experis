#include "tcpClient.hpp"
#include "exceptions.hpp"
#include "testFunc.hpp"
#include <iostream>
using namespace std;
using namespace kokfikoCDR;
using namespace exceptions;

static void TestCreateClient(const TcpClient& a_client) {
    static int testNum = 0;
    a_client.SendMessage("message from client");
    PrintResult("send data", true, testNum, ": \t");
}

int main() {
    static int testNum = 0;
    try {
        TcpClient client;
        client.ConnectToServer();
        PrintResult("create client", true, testNum, ": \t");
      
        TestCreateClient(client);

    }catch(const exception& exc) {
        cout << exc.what() << endl;
        PrintResult("create client or send data", false, testNum, ": \t");
    }

    return 0;
}
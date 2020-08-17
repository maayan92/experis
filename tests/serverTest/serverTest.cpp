#include "serverManager.hpp"
#include "testFunc.hpp"
#include <iostream>
using namespace kokfikoCDR;
using namespace std;

static void TestCreateServer() {
    static int testNum = 0;
     try {
         TcpServer server("127.0.0.1", 1234);
         PrintResult("create sevrer", true, testNum, ": \t");

     }catch(const exception& exc) {
         cout << exc.what() << endl;
         PrintResult("create sevrer", false, testNum, ": \t");
     }
}

static void TestGetMessage() {
    static int testNum = 0;
     try {
         TcpServer server("127.0.0.1", 1234);
         int activity = 1;
         server.GetSocketConnection(activity);
         //server.WaitForMessage();
         PrintResult("create sevrer", true, testNum, ": \t");

     }catch(const exception& exc) {
         cout << exc.what() << endl;
         PrintResult("create sevrer", false, testNum, ": \t");
     }
}

int main() {

    //TcpServer server;
    //GetSocketConnection(0);

    TestCreateServer();


/*
    try {
        ofstream outputFile("../cdrFileReaderTest/result.txt");
        ServerManager serverMng(outputFile);

        serverMng.RunServer();
    }catch(const exception& exc) {
        cout << exc.what() << endl;
    }
*/
    return 0;
}
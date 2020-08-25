#include "tcpServer.hpp"
#include "cdrRecord.hpp"
#include "testFunc.hpp"
#include <iostream>
using namespace kofiko;
using namespace std;

static const size_t BUFFER_SIZE = 200; 

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

static void TestGetConnection() {
    static int testNum = 0;
     try {
         TcpServer server("127.0.0.1", 1234);
         int activity = 1;
         server.SetSocketConnection();
         PrintResult("create sevrer", true, testNum, ": \t");

     }catch(const exception& exc) {
         cout << exc.what() << endl;
         PrintResult("create sevrer", false, testNum, ": \t");
     }
}

static void TestGetData() {
    static int testNum = 0;
     try {
         TcpServer server("127.0.0.1", 1234);
         int activity = 1;
         server.SetSocketConnection();
         char buffer[BUFFER_SIZE];
         server.GetData(buffer, BUFFER_SIZE);
         cout << buffer;
         PrintResult("create sevrer", true, testNum, ": \t");

     }catch(const exception& exc) {
         cout << exc.what() << endl;
         PrintResult("create sevrer", false, testNum, ": \t");
     }
}

int main() {

    TestCreateServer();
    TestGetConnection();
    TestGetData();

    return 0;
}
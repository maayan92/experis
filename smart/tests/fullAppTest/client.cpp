#include "clientTcp.hpp"
#include "protocol.hpp"
#include <iostream>
#include <sstream>      // std::stringstream
using namespace std;
using namespace experis;
using namespace smart_house;

enum {
    SEND_MSG,
    EXIT
};

static void RunClient(ClientTcp& a_client, string& a_deviceId)
{
    size_t action;
    cout << "please press " << SEND_MSG << " to send new message or " << EXIT << " to exit";
    cin >> action;

    string msg;

    while(EXIT != action) {

        msg.clear();
        cout << "please enter event message to send to server \n";
        cin >> msg;

        time_t t;
        time(&t);
        struct tm* eventTime = localtime(&t);
        SensorInfo info(a_deviceId, msg.c_str(), eventTime);
        msg.clear();
        Protocol::Pack(msg, info);

        try {
            a_client.SendMessage(msg);

        }catch(exception& exc) {
            cout << exc.what();
        }

        cout << "please press " << SEND_MSG << " to send new message or " << EXIT << " to exit";
        cin >> action;
    }
}

// run at terminal like - outPut file IP number PORT number device id.
int main(int argc, char* argv[])
{
    if(argc != 4) {
        cout << "please enter IP and PORT numbers and device id when running the client! \n";
        return 0;
    }

    stringstream port(argv[2]);
    size_t portNum;
    port >> portNum;
    string deviceId(argv[3]);

    ClientTcp client(argv[1], portNum);
    client.ConnectToServer();

    RunClient(client, deviceId);

    return 0;
}
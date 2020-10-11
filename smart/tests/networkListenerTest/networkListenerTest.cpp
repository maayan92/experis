//#include "mu_test.h"
#include <iostream>
#include "networkListener.hpp"
#include "iMessageHandler.hpp"
using namespace std;
using namespace experis;

class MsgHandler : public IMessageHandler {

    virtual void HandleMsg(const char* a_msg)
    {
        cout << a_msg << '\n';
    }

};

int main()
{ 
    MsgHandler handler;
    try {
        NetworkListener listener("127.0.0.1", 1234, handler);
        listener.ListenEvents();
    } catch(const exception& exc) {
        cout << exc.what() << '\n';
    }

    return 0;
}
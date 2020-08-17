#ifndef SERVER_MANAGER_H
#define SERVER_MANAGER_H

#include "reciever.hpp"
#include <iosfwd>
#include <fstream>

namespace kokfikoCDR {

class ServerManager {
public:
    ServerManager(std::ostream& m_outPutRecords);
    //~ServerManager() = default;

    void RunServer();

private:
    ServerManager(const ServerManager& a_serverManager);
    ServerManager& operator=(const ServerManager& a_serverManager);

    void setConnection(int& a_activity);
    void runAllClientsRequests(int& a_activity);

private:
    static const size_t DATA_SIZE = 200;

    TcpServer m_server;
    std::vector<int> m_clients;
    std::ostream& m_outPutRecords;
};

} // kokfikoCDR

#endif
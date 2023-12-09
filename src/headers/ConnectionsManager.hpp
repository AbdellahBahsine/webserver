#ifndef CONNECTIONSMANAGER_HPP
#define CONNECTIONSMANAGER_HPP

#include"libs.hpp"
#include"MyServer.hpp"


class ConnectionsManager {
    public:
        ConnectionsManager();
        ~ConnectionsManager();
        
        void socketMonitore();
        // void recvRequest();
        void acceptNewIncommingConnections(MyServer *serverId);
        int recvRequest(int clientFd,MyServer* serverId);
        void addFdToTheSet(int clientFd);
        // void changeClinetMonitoringEvent(int clinetFd);
        void addServerToTheSet(MyServer &serverInstance);
    private:
        std::vector<MyServer> serversSet;
        std::vector<struct pollfd> masterFdSet;
        int serverCount;
};








#endif
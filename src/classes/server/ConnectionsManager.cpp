#include"../../headers/ConnectionsManager.hpp"



ConnectionsManager::ConnectionsManager() {
    (*this).serverCount = 0;
}

ConnectionsManager::~ConnectionsManager() {

}

void ConnectionsManager::addServerToTheSet(MyServer &serverInstance) {
    (*this).serversSet.push_back(serverInstance);
    (*this).serverCount++;

    std::vector<struct pollfd> clientFdSet = serverInstance.getClientFdSet();
    std::vector<struct pollfd>::iterator it = clientFdSet.begin();

    (*this).masterFdSet.push_back((*it));

}

void ConnectionsManager::addFdToTheSet(int clientFd) {
    if (clientFd < 0) {
        Log::e("Invalid Client FD ...");
        return;
    }
    struct pollfd client;
    client.fd = clientFd;
    client.events = POLLIN;
    client.revents = 0;
    (*this).masterFdSet.push_back(client);
}

void ConnectionsManager::acceptNewIncommingConnections(MyServer *serverId) {
    ClientProfile client;

    client.address_length = sizeof(client.address);
    client.SocketFD = accept(serverId->getListenSocketFd(),(struct sockaddr*)&client.address,&client.address_length);
    if(client.SocketFD < 0) {
        Log::e("accept Failed ...");
        exit(1);
    }
    setSocketNonBlocking(client.SocketFD);
    addFdToTheSet(client.SocketFD);
    serverId->AddFdToPollFds(client.SocketFD);
    char address_buffer[100];
    getnameinfo((struct sockaddr*)&client.address, client.address_length, address_buffer, sizeof(address_buffer), 0, 0, NI_NUMERICHOST);
    std::string ipAdress(address_buffer);
    client.ipAdress = ipAdress;
    serverId->AddToClientProfiles(client);
    Log::d("New client connected: " + ipAdress + " on Port " + serverId->getServerPort());
}



void ConnectionsManager::socketMonitore() {
    while (true) {
        if (poll(masterFdSet.data(), masterFdSet.size(), 0) < 0) {
            Log::e("POLL FAILED ...");
            exit(1);
        }
        for (std::vector<MyServer>::iterator serverId = serversSet.begin(); serverId != serversSet.end(); ++serverId) {
            for (std::vector<struct pollfd>::iterator fdIt = serverId->getClientFdSet().begin(); fdIt != serverId->getClientFdSet().end(); ++fdIt) {
                if (fdIt->revents & POLLIN) {
                    if(fdIt == serverId->getClientFdSet().begin()) {
            std::cout << "hello world" << std::endl;
                        acceptNewIncommingConnections(&(*serverId));
                    }
                    else {
                        std::cout << "hello world" << std::endl;
                    }
                }
            }
        }
    }
}






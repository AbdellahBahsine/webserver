#ifndef INITSERVER_HPP
#define INITSERVER_HPP


#include"libs.hpp"
#include"ConfigurationFile.hpp"
#include"ClientProfile.hpp"
#include"logger.hpp"




class MyServer {
    public:
        MyServer(s_server &serverInfos);
        ~MyServer();
        
        //SETTERS
        void setListenAdressPort(t_server &serverInfo);
        void setListenSocket(int socketFd);
        void AddFdToPollFds(int clientFd);
        void AddToClientProfiles(ClientProfile &client);

        //GETTERS
        int getListenSocketFd();
        std::string getServerPort();
        std::string getListenAdress();
        std::vector<struct ClientProfile>& getClientProfilesSet();
        std::vector<struct pollfd>& getClientFdSet();

        //OTHER MEMBERS FUNCTIONS
        void setupServerConfiguration();
        void dropClient(int clientFd);
    private:

        t_server *serverInformations;
        std::string listenAdress;
        int serverPort;
        int listenSocket;
        struct addrinfo hint;
        struct addrinfo *bindAddress;
        std::vector<struct pollfd> serverPollFd;
        std::vector<struct ClientProfile> clientProfiles;
        const int backLog;
};




#endif
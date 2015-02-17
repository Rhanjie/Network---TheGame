#ifndef CLIENT_HPP_INCLUDED
#define CLIENT_HPP_INCLUDED
#include "networkManager.hpp"
#include "managerLibs.hpp"
#include "players.hpp"

namespace rha{
    class cClient{
        private:
         cServerInfo server;
         cPlayer player;

         std::string nick;
         bool isConnect;
        public:
         cNetworkManager manager;
         sf::TcpSocket socket;

         cClient();
         void connect(sf::IpAddress ip, unsigned short port, std::string nick);
         bool login(std::string nick);
         void disconnect();

         inline bool getConnect(){return isConnect;}
    };
}

#endif // CLIENT_HPP_INCLUDED

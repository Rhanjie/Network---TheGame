#ifndef CLIENT_HPP_INCLUDED
#define CLIENT_HPP_INCLUDED
#include "networkManager.hpp"
#include "managerLibs.hpp"
#include "player.hpp"

namespace rha{
    class cClient{
        private:
         cPlayer player;
         cServerInfo server;
         cNetworkManager manager;

         sf::TcpSocket socket;
         std::string nick;
         bool isConnect;
        public:
         cClient();
         void connect(sf::IpAddress ip, unsigned short port);
         //registration&login todo..
         void disconnect();


         inline bool getConnect(){return isConnect;}
    };
}

#endif // CLIENT_HPP_INCLUDED

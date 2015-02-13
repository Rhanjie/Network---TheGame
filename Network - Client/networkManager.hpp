#ifndef NETWORKMANAGER_HPP_INCLUDED
#define NETWORKMANAGER_HPP_INCLUDED
#include "managerLibs.hpp"
#include "server.hpp"

namespace rha{
    class cNetworkManager{
        private:
         std::string typePacket;
         sf::Packet dataPacket;
        public:
         bool sendPacket(sf::TcpSocket* socket, sf::Packet packet);
         bool sendRawPacket(sf::TcpSocket* socket, std::string packet);
         bool receivePacket(sf::TcpSocket* socket); /*dataSaveInObject*/

         inline std::string getLastTypePacket(){return typePacket;}
         inline sf::Packet &getLastPacket(){return dataPacket;}
    };
}

#endif // NETWORKMANAGER_HPP_INCLUDED

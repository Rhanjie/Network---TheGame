#ifndef NETWORKMANAGER_HPP_INCLUDED
#define NETWORKMANAGER_HPP_INCLUDED
#include <typePackets.hpp>
#include "managerLibs.hpp"
#include "server.hpp"

namespace rha{
    class cNetworkManager{
        private:
         typePacketsInServer tLastPacketReceive;
         sf::Packet dataPacket, sPacket;

         int converter=0;
        public:
         bool sendPacket(sf::TcpSocket* socket, sf::Packet* packet);
         bool sendRawPacket(sf::TcpSocket* socket, typePacketsInClient packet);
         bool receivePacket(sf::TcpSocket* socket); /*dataSaveInObject*/

         inline typePacketsInServer getLastTypePacket(){return tLastPacketReceive;}
         inline sf::Packet &getLastPacket(){return dataPacket;}
    };
}

#endif // NETWORKMANAGER_HPP_INCLUDED

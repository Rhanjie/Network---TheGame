#ifndef NETWORKMANAGER_HPP_INCLUDED
#define NETWORKMANAGER_HPP_INCLUDED
#include "managerLibs.hpp"
#include <typePackets.hpp>

namespace rha{
    class cNetworkManager{
        private:
         typePacketsInClient tLastPacketReceive;
         sf::Packet dataPacket;
        public:
         bool sendPacket(sf::TcpSocket* socket, sf::Packet packet);
         bool sendRawPacket(sf::TcpSocket* socket, typePacketsInServer tPacketSend);
         bool receivePacket(sf::TcpSocket* socket); /*dataSaveInObject*/

         inline typePacketsInClient getLastTypePacket(){return tLastPacketReceive;}
         inline sf::Packet &getLastPacket(){return dataPacket;}
    };
}

#endif // NETWORKMANAGER_HPP_INCLUDED

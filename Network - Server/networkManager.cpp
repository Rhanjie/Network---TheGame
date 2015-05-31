#include "networkManager.hpp"

bool rha::cNetworkManager::sendPacket(sf::TcpSocket* socket, sf::Packet packet){
    if(socket->send(packet)==sf::Socket::Done)
     return true;
    else return false;
}

bool rha::cNetworkManager::sendRawPacket(sf::TcpSocket* socket, rha::typePacketsInServer typePacket){
    sf::Packet packet;

    packet<<typePacket;
    if(socket->send(packet)==sf::Socket::Done)
     return true;
    else return false;
}

bool rha::cNetworkManager::receivePacket(sf::TcpSocket* socket){
    int converter=0;

    if(socket->receive(this->dataPacket)==sf::Socket::Done){
        if(this->dataPacket>>converter){
            tLastPacketReceive=static_cast<rha::typePacketsInClient>(converter);

            return true;
        } else return false;
    }else{tLastPacketReceive=rha::typePacketsInClient::NORMAL_CLIENT_NULL;
        return false;
    }
}

#include "networkManager.hpp"

bool rha::cNetworkManager::sendPacket(sf::TcpSocket* socket, sf::Packet packet){
    if(socket->send(packet)==sf::Socket::Done)
     return true;
    else return false;
}

bool rha::cNetworkManager::sendRawPacket(sf::TcpSocket* socket, rha::typePacketsInClient typePacket){
    sf::Packet packet;
    packet<<int(typePacket);

    if(socket->send(packet)==sf::Socket::Done)
     return true;
    else return false;
}

bool rha::cNetworkManager::receivePacket(sf::TcpSocket* socket){
    int converter;

    if(socket->receive(this->dataPacket)==sf::Socket::Done){
        if(this->dataPacket>>converter){
            tLastPacketReceive=static_cast<rha::typePacketsInServer>(converter); return true;
        } else return false;
    }else{
        this->dataPacket<<rha::typePacketsInServer::NORMAL_SERVER_NULL;
        this->dataPacket>>converter;
        tLastPacketReceive=static_cast<rha::typePacketsInServer>(converter);
        return false;
    }
}

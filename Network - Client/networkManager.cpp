#include "networkManager.hpp"

bool rha::cNetworkManager::sendPacket(sf::TcpSocket* socket, sf::Packet packet){
    std::string type="NULL";

    if(packet>>type); else return false; //todo - if(!packet>>type)
    if(socket->send(packet)==sf::Socket::Done)
     return true;
    else return false;
}

bool rha::cNetworkManager::sendRawPacket(sf::TcpSocket* socket, std::string content){
    sf::Packet packet;
    packet<<content;

    if(socket->send(packet)==sf::Socket::Done)
     return true;
    else return false;
}

bool rha::cNetworkManager::receivePacket(sf::TcpSocket* socket){
    if(socket->receive(this->dataPacket)==sf::Socket::Done){
        if(this->dataPacket>>typePacket)
         return true;
        else return false;
    }else{
        this->dataPacket<<"NORMAL_DATA_NULL";
        this->dataPacket>>typePacket;
        return false;
    }
}

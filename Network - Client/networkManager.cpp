#include "networkManager.hpp"

bool rha::cNetworkManager::sendPacket(sf::TcpSocket* socket, sf::Packet* packet){
    if(socket->send(*packet)==sf::Socket::Done)
     return true;
    else return false;
}

bool rha::cNetworkManager::sendRawPacket(sf::TcpSocket* socket, rha::typePacketsInClient typePacket){
    sPacket<<typePacket;

    if(socket->send(sPacket)==sf::Socket::Done){sPacket.clear(); return true;}
     else{sPacket.clear(); return false;}
}

bool rha::cNetworkManager::receivePacket(sf::TcpSocket* socket){
    if(socket->receive(this->dataPacket)==sf::Socket::Done){
        if(this->dataPacket>>converter){
            tLastPacketReceive=static_cast<rha::typePacketsInServer>(converter);

            return true;
        } else return false;
    }else{tLastPacketReceive=rha::typePacketsInServer::NORMAL_SERVER_NULL;
        return false;
    }
}

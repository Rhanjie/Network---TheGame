#include "server.hpp"

rha::cServerInfo::cServerInfo(){
    this->ip="";
    this->port=0;

    socket.setBlocking(0);
}void rha::cServerInfo::setData
  (sf::IpAddress ip, unsigned short port){
    this->ip=ip;
    this->port=port;
}

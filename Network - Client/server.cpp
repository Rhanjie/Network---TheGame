#include "server.hpp"

rha::cServerInfo::cServerInfo(){
    this->ip="";
    this->port=NULL;
}void rha::cServerInfo::setData
  (sf::IpAddress ip, unsigned short port){
    this->ip=ip;
    this->port=port;
}

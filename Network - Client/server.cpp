#include "server.hpp"

void rha::cServerInfo::setData
  (sf::IpAddress ip, unsigned short port){
    this->ip=ip;
    this->port=port;
}

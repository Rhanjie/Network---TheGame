#ifndef SERVER_HPP_INCLUDED
#define SERVER_HPP_INCLUDED
#include "managerLibs.hpp"

namespace rha{
    class cServerInfo{
        private:
         sf::IpAddress ip;
         unsigned short port;
        public:
         sf::TcpSocket socket;
         cServerInfo();

         void setData(sf::IpAddress ip, unsigned short port);

         inline sf::IpAddress getIP(){return ip;}
         inline unsigned short getPort(){return port;}
         inline sf::TcpSocket* getSocket(){return &socket;}
    };
}

#endif // SERVER_HPP_INCLUDED

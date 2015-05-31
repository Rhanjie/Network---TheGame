#ifndef SERVER_HPP_INCLUDED
#define SERVER_HPP_INCLUDED
#include "managerLibs.hpp"

namespace rha{
    class cServerInfo{
        private:
         sf::IpAddress ip="";
         unsigned short port=0;
        public:
         void setData(sf::IpAddress ip, unsigned short port);

         inline sf::IpAddress getIP(){return ip;}
         inline unsigned short getPort(){return port;}
    };
}

#endif // SERVER_HPP_INCLUDED

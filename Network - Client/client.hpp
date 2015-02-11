#ifndef CLIENT_HPP_INCLUDED
#define CLIENT_HPP_INCLUDED
#include "managerLibs.hpp"
#include "player.hpp"
#include "server.hpp"

namespace rha{
    class cClient{
        private:
         cPlayer* player;
         cServerInfo* server;

         std::string nick;
         std::string password;

         bool isConnect;
        public:
         cClient(cServerInfo* server=nullptr);
         void connect(/*sf::IpAddress ip, unsigned short port*/);
         void disconnect();

         //registration&login todo..
         inline bool getConnect(){return isConnect;}
    };
}

#endif // CLIENT_HPP_INCLUDED

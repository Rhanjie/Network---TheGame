#ifndef CLIENTS_HPP_INCLUDED
#define CLIENTS_HPP_INCLUDED
#include "managerLibs.hpp"
#include "player.hpp"

namespace rha{
    class cClient{
        private:
        public:
         cClient(sf::TcpSocket* socket, std::string nick);

         sf::TcpSocket* socket;
         cPlayer* player=nullptr;
         std::string nick;

         //...
    };
}

#endif // CLIENTS_HPP_INCLUDED

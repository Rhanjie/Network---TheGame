#ifndef CLIENTS_HPP_INCLUDED
#define CLIENTS_HPP_INCLUDED
#include "managerLibs.hpp"

namespace rha{
    class cClient{
        private:
         std::string nick;
        public:
         cClient(sf::TcpSocket* socket, std::string nick);
         sf::TcpSocket* socket;

         //...
    };
}

#endif // CLIENTS_HPP_INCLUDED

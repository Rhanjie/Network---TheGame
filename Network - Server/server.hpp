#ifndef SERVER_HPP_INCLUDED
#define SERVER_HPP_INCLUDED
#include "managerLibs.hpp"
#include "networkManager.hpp"
#include "clients.hpp"

namespace rha{
    class cServer{
        private:
         //sf::TcpListener listener;
         //sf::SocketSelector selector;

         cNetworkManager manager;
         std::vector<cClient>vClients;
        public:
         //sf::TcpListener listener; //todo
         sf::SocketSelector selector;

         bool listening(sf::TcpListener* listener, unsigned int port);
         bool findNewConnection(sf::TcpListener* listener);
         void serveClients();
    };
}

#endif // SERVER_HPP_INCLUDED

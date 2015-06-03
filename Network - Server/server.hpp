#ifndef SERVER_HPP_INCLUDED
#define SERVER_HPP_INCLUDED
#include "managerLibs.hpp"
#include "networkManager.hpp"
#include "clients.hpp"
#include "map.hpp"

namespace rha{
    class cServer{
        private:
         cNetworkManager manager;
         std::vector<cClient>vClients;
        public:
         sf::TcpListener* listener=nullptr; //todo
         rha::cMap tMap;

         void serveClients();

         void receiveData(tgui::Gui* gui, bool* run, bool* stop);
         void findNewConnection(tgui::Gui* gui, bool* run, bool* stop);
         bool listening(sf::TcpListener* listener, unsigned int port);

         void sendAll(short &which, sf::Packet* packet);
         void releaseResources();

         inline void setListenerPtr(sf::TcpListener* listener){
            this->listener=listener; listener->setBlocking(0);
        }
    };
}

#endif // SERVER_HPP_INCLUDED

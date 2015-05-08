#ifndef SERVER_HPP_INCLUDED
#define SERVER_HPP_INCLUDED
#include "managerLibs.hpp"
#include "networkManager.hpp"
#include "clients.hpp"

namespace rha{
    class cServer{
        private:
         cNetworkManager manager;
         std::vector<cClient>vClients;
         tgui::Gui* gui=nullptr;
        public:
         sf::TcpListener* listener=nullptr; //todo - test

         bool listening(sf::TcpListener* listener, unsigned int port);
         void findNewConnection();
         void serveClients();
         void receiveData();

         inline void setGUIPtr(tgui::Gui* gui){this->gui=gui;}
         inline void setListenerPtr(sf::TcpListener* listener){this->listener=listener; listener->setBlocking(true);}
    };
}

#endif // SERVER_HPP_INCLUDED

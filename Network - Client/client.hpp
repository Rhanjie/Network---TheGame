#ifndef CLIENT_HPP_INCLUDED
#define CLIENT_HPP_INCLUDED
#include "networkManager.hpp"
#include "loaderTextures.hpp"
#include "otherPlayers.hpp"
#include "managerLibs.hpp"
#include "player.hpp"
#include "tile.hpp"
#include "map.hpp"

namespace rha{
    /*Manage the main player and other clients*/
     class cClient{
        public:
         enum eStatus{NOTCONNECT, WATCHING, PLAYING};
         std::vector<cOtherPlayer>vOtherPlayers;
        private:
         cServerInfo server;
         cPlayer player;
         cMap mapGame;

         sf::Clock clock; sf::Time timer;

         eStatus status;
        public:
         cNetworkManager manager;
         sf::TcpSocket socket;

         cClient();
         void connect(sf::IpAddress ip, unsigned short port, std::string nick);
         bool login(std::string nick);
         void disconnect();

         void managePlayer(sf::Event event);
         void updateAll(sf::RenderWindow& window);
         void drawAll(sf::RenderWindow& window);

         inline bool getStatus(){return status;}
         inline sf::View getView(){return player.view;}
    };
}

#endif // CLIENT_HPP_INCLUDED

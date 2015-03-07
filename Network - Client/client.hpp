#ifndef CLIENT_HPP_INCLUDED
#define CLIENT_HPP_INCLUDED
#include "networkManager.hpp"
#include "managerLibs.hpp"
#include "otherPlayers.hpp"
#include "loaderTextures.hpp"
#include "player.hpp"

namespace rha{
    class cClient{
        public:
         enum eStatus{NOTCONNECT, WATCHING, PLAYING};
         std::vector<cOtherPlayer>vOtherPlayers;
         cPlayer player;
        private:
         cServerInfo server;
         cLoaderTexture loaderTexture;
         sf::Clock clock; sf::Time timer;
         //cPlayer player;

         eStatus status;
        public:
         cNetworkManager manager;
         sf::TcpSocket socket;

         cClient();
         void connect(sf::IpAddress ip, unsigned short port, std::string nick);
         bool login(std::string nick);
         bool join();
         void managePlayer(sf::Event event);
         void updateAll(sf::RenderWindow& window);
         void drawAll(sf::RenderWindow& window);
         void disconnect();

         inline bool getStatus(){return status;}
    };
}

#endif // CLIENT_HPP_INCLUDED

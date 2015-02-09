#ifndef GAMEMANAGER_HPP_INCLUDED
#define GAMEMANAGER_HPP_INCLUDED
#include "managerLibs.hpp"
#include "helper.hpp"
#include "server.hpp"
#include "client.hpp"

namespace rha{
    class cGameManager{
        private:
         sf::RenderWindow window;
         sf::Event event;
         sf::Font font;

         cServerInfo server;
         //cClient client(&server);

         void menu();
        protected:
         enum gameState{MENU, GAME, END};
            gameState state;

        public:
         cGameManager(sf::Vector2i size, std::string title);
         //~cGameManager();

         void runGame();
    };
}

#endif // GAMEMANAGER_HPP_INCLUDED

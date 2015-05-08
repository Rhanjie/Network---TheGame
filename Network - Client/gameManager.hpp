#ifndef GAMEMANAGER_HPP_INCLUDED
#define GAMEMANAGER_HPP_INCLUDED
#include "managerLibs.hpp"
#include "connector.hpp"

namespace rha{
    class cGameManager{
        private:
         tgui::Callback callback;
         sf::RenderWindow window;

         cClient client;

         void runMenu();
         void runGame();
        protected:
         enum gameState{MENU, GAME, END};
            gameState state;

        public:
         cGameManager(sf::Vector2i size, std::string title);
         //~cGameManager();

         void runApp();
    };
}

#endif // GAMEMANAGER_HPP_INCLUDED

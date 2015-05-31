#ifndef GAMEMANAGER_HPP_INCLUDED
#define GAMEMANAGER_HPP_INCLUDED
#include "managerLibs.hpp"
#include "connector.hpp"

namespace rha{
    class cGameManager{
        public:
         cGameManager(sf::Vector2i size, std::string title);
         //~cGameManager();

         void manageApp();
        private:
         sf::RenderWindow window;
          sf::Event event;

          tgui::Gui gui{window};
         tgui::Callback callback;
          rha::cClient client;

         void sMenu();
         void sRunning();
        protected:
         enum gameState{MENU, GAME, END};
            gameState state;
    };
}

#endif // GAMEMANAGER_HPP_INCLUDED

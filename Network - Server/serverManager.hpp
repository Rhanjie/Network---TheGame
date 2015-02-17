#ifndef SERVERMANAGER_HPP_INCLUDED
#define SERVERMANAGER_HPP_INCLUDED
#include "managerLibs.hpp"
#include "connector.hpp"

namespace rha{
    class cServerManager{
        private:
         tgui::Callback callback;
         sf::RenderWindow window;
         sf::Event event;
         sf::Font font;

         rha::cServer server;

         void configure();
         void running();
        protected:
         enum serverState{WAIT, RUN, END};
          serverState state;
        public:
         cServerManager(sf::Vector2i size, std::string title);

         void runApp();
    };
}

#endif // SERVERMANAGER_HPP_INCLUDED

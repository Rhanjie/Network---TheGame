#ifndef SERVERMANAGER_HPP_INCLUDED
#define SERVERMANAGER_HPP_INCLUDED
#include "managerLibs.hpp"
#include "connector.hpp"

namespace rha{
    class cServerManager{
        public:
         cServerManager(sf::Vector2i size, std::string title);

         void manageApp(); //main while
        private:
         sf::RenderWindow window;
          sf::Event event;

          tgui::Gui gui{window};
         tgui::Callback callback;
          rha::cServer server;

         void sConfigure();
         void sRunning();
        protected:
         enum serverState{WAIT, RUN, END};
          serverState state;
    };
}

#endif // SERVERMANAGER_HPP_INCLUDED

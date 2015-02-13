#ifndef LOADERGUI_HPP_INCLUDED
#define LOADERGUI_HPP_INCLUDED
#include "managerLibs.hpp"

namespace rha{
    class cLoaderGUI{
        private:
         enum stateServer{MAIN, OPTION};
         stateServer state;
        public:
         cLoaderGUI(){state=MAIN;}
         void loadMenuGUI(tgui::Gui &gui);
         void loadGameGUI(tgui::Gui &gui);

         inline void setState(stateServer state){this->state=state;}
    };
}

#endif // LOADERGUI_HPP_INCLUDED

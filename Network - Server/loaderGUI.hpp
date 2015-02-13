#ifndef LOADERGUI_HPP_INCLUDED
#define LOADERGUI_HPP_INCLUDED
#include "managerLibs.hpp"

namespace rha{
    class cLoaderGUI{
        private:
         enum stateServer{WAIT, RUN};
         stateServer state;
        public:
         cLoaderGUI(){state=WAIT;}
         void loadServerGUI(tgui::Gui &gui);

         inline void setState(stateServer state){this->state=state;}
    };
}

#endif // LOADERGUI_HPP_INCLUDED

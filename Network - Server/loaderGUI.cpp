#include "loaderGUI.hpp"

void rha::cLoaderGUI::loadServerGUI(tgui::Gui &gui){
    gui.removeAllWidgets();

    if(state==WAIT){
        tgui::Button::Ptr bStart(gui, "start");

        bStart->load("media/Black.conf");
        bStart->setSize(120, 40);
        bStart->setPosition(200, 140);
        bStart->setText("Run server");
    }else if(state==RUN){
        //...
    }
};

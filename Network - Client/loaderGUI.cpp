#include "loaderGUI.hpp"

void rha::cLoaderGUI::loadMenuGUI(tgui::Gui &gui){
    gui.removeAllWidgets();

    if(state==MAIN){
        tgui::EditBox::Ptr eBoxIP(gui, "ip");

        eBoxIP->load("media/Black.conf");
        eBoxIP->setSize(400, 40);
        eBoxIP->setPosition(200, 140);
        eBoxIP->setText("localhost");
    }else if(state==OPTION){
        //...
    }
};

void rha::cLoaderGUI::loadGameGUI(tgui::Gui &gui){
    gui.removeAllWidgets();
    //...
}

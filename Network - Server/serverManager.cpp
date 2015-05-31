#include "serverManager.hpp"

rha::cServerManager::cServerManager(sf::Vector2i size, std::string title){
    window.create(sf::VideoMode(size.x, size.y, 32), title, sf::Style::Close);
    if(!cManagerResources::getObj().isLoaded()){
        std::cout<<"Error: Loading resources failed!\n";

        state=END; //todo - logger.
    } else{gui.setGlobalFont(*cManagerResources::getObj().getFont()); state=WAIT;}
} void rha::cServerManager::manageApp(){
    while(window.isOpen()){
        switch(state){
            case WAIT:
              this->sConfigure();
               break;
            case RUN:
              this->sRunning();
               break;
            case END:
              window.close();
               break;
        }
    }
}

void rha::cServerManager::sConfigure(){
    gui.loadWidgetsFromFile("media/waitForm.RhAf");

    while(state==WAIT){
        while(window.pollEvent(event)){
            switch(event.type){
             case sf::Event::Closed:
                state=END; break;

                //...
            }

            gui.handleEvent(event);
        } while(gui.pollCallback(callback)){
            switch(callback.id){
             case 1: state=RUN; break;
             case 2: state=END; break;
            }

            //todo - add options
        }

        window.clear();
        gui.draw();

        window.display();
    }
}

#include "serverManager.hpp"

rha::cServerManager::cServerManager(sf::Vector2i size, std::string title){
    window.create(sf::VideoMode(size.x, size.y, 32), title, sf::Style::Close);
    if(!font.loadFromFile("media/font.ttf")){
        state=END; return;
    } else state=WAIT;
} void rha::cServerManager::runApp(){
    while(window.isOpen()){
        switch(state){
            case WAIT:
             configure(); break;
            case RUN:
             running(); break;
            case END:
             window.close(); break;
        }
    }
}

void rha::cServerManager::configure(){
    tgui::Gui gui(window);
    gui.setGlobalFont(font);

    gui.loadWidgetsFromFile("media/waitForm.RhAf");

    while(state==WAIT){
        while(window.pollEvent(event)){
            switch(event.type){
             case sf::Event::Closed:
                state=END; break;
             default: break;
            }
            gui.handleEvent(event);
        } while(gui.pollCallback(callback)){
            if(callback.id==1){state=RUN; break;}
            else if(callback.id==2){state=END; break;}
        }

        window.clear();
        gui.draw();

        window.display();
    }
}

void rha::cServerManager::running(){
    sf::TcpListener listener;
    tgui::Gui gui(window);

    gui.setGlobalFont(font);
    server.listening(&listener, 7415);
    gui.loadWidgetsFromFile("media/runForm.RhAf");

    while(state==RUN){
        while(window.pollEvent(event)){
            switch(event.type){
             case sf::Event::Closed:
                state=END; break;
             default: break;
            }
            gui.handleEvent(event);
        } while(gui.pollCallback(callback)){
            if(callback.id==1){state=WAIT; break;}
        }

        if((server.selector).wait(sf::seconds(0.02))){
            server.findNewConnection(&listener, gui);
            server.serveClients(gui);
        }

        window.clear();
        gui.draw();

        window.display();
    }
}

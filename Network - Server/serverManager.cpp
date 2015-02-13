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
             /*running();*/ break;
            case END:
             window.close(); break;
        }
    }
}

void rha::cServerManager::configure(){
    sf::TcpListener listener;
    tgui::Gui gui(window);
    gui.setGlobalFont(font);
    loader.loadServerGUI(gui);

    server.listening(&listener, 7415);

    sf::Event event;
    while(state==WAIT){
        while(window.pollEvent(event)){
            switch(event.type){
             case sf::Event::Closed:
                state=END; break;
             default: break;
            }
            gui.handleEvent(event);
        }

        if((server.selector).wait(sf::seconds(0.02))){ //todo - only test
            server.findNewConnection(&listener);
            server.serveClients(); //todo - test
        }

        window.clear();
        gui.draw();

        window.display();
    }
}

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
    server.setGUIPtr(&gui);

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

    sf::Clock clock; //for fixed step loop
    sf::Time time, timeOfUpdate=sf::Time::Zero;
    const sf::Time timeStep=sf::seconds(1/60.f);

    gui.setGlobalFont(font);
    server.listening(&listener, 7415);
    gui.loadWidgetsFromFile("media/runForm.RhAf");
    server.setGUIPtr(&gui);

    std::thread connectThread(&rha::cServer::findNewConnection, &server);
    std::thread receiveThread(&rha::cServer::receiveData, &server);

    while(state==RUN){
        time=clock.restart();

        timeOfUpdate+=time;
        while(timeOfUpdate>timeStep){
            timeOfUpdate-=timeStep;
            while(window.pollEvent(event)){
                switch(event.type){
                 case sf::Event::Closed:
                    state=WAIT; break;
                 default: break;
                }
                gui.handleEvent(event);
            } while(gui.pollCallback(callback)){
                if(callback.id==1){state=WAIT; break;}
            }

            server.serveClients();
        }

        window.clear();
        gui.draw();

        window.display();
    }
}

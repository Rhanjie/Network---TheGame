#include "gameManager.hpp"

rha::cGameManager::cGameManager(sf::Vector2i size, std::string title){
    window.create(sf::VideoMode(size.x, size.y, 32), title, sf::Style::Close);
    if(!(cManagerResources::getObj()).isLoaded()){
        state=END; return;
    } else state=MENU;
} void rha::cGameManager::runApp(){
    while(window.isOpen()){
        switch(state){
            case MENU:
             this->runMenu(); break;
            case GAME:
             this->runGame(); break;
            case END:
             window.close(); break;
        }
    }
}

/*-------------*/

void rha::cGameManager::runMenu(){
    sf::Vector2f mouse;

    tgui::Gui gui(window);
    gui.setGlobalFont(*cManagerResources::getObj().getFont());
    gui.loadWidgetsFromFile("media/oldStyle/menuForm.RhAf");

    sf::Event event;
    while(state==MENU){
        if(client.getStatus()==cClient::WATCHING||client.getStatus()==cClient::PLAYING) state=GAME;
        mouse=static_cast<sf::Vector2f>(sf::Mouse::getPosition(window));
        while(window.pollEvent(event)){
            switch(event.type){
             case sf::Event::Closed:
                state=END; break;
             default: break;
            }
            gui.handleEvent(event);
        } while(gui.pollCallback(callback)){
            if(callback.id==1){
                tgui::EditBox::Ptr eBoxCopy1=gui.get("EditBox1");
                tgui::EditBox::Ptr eBoxCopy2=gui.get("EditBox2");

                std::thread thrConnect(&rha::cClient::connect, &client, std::string(eBoxCopy1->getText()),
                 7415, std::string(eBoxCopy2->getText())); thrConnect.detach();
            }
            else if(callback.id==2){state=END; break;}
        }

        window.clear();
        gui.draw();

        window.display();
    }
}

void rha::cGameManager::runGame(){
    sf::Text title("Game is created...", *cManagerResources::getObj().getFont(), 50); //todo - only test
    title.setOrigin(title.getGlobalBounds().width/2, 50/2);
    title.setPosition((window.getSize()).x/2, 75);

    sf::Clock clock; //for fixed step loop
    sf::Time timeOfUpdate=sf::Time::Zero;
    const sf::Time timeStep=sf::seconds(1/60.f);

    tgui::Gui gui(window);
    gui.setGlobalFont(*cManagerResources::getObj().getFont());
    gui.loadWidgetsFromFile("media/oldStyle/gameForm.RhAf");

    sf::Event event;
    while(state==GAME){
        sf::Time time=clock.restart();

        timeOfUpdate+=time;
        while(timeOfUpdate>timeStep){
            timeOfUpdate-=timeStep;
            while(window.pollEvent(event)){
                client.managePlayer(event);
                switch(event.type){
                 case sf::Event::Closed:
                    client.disconnect(); state=MENU; break;
                 default: break;
                }
                gui.handleEvent(event);
            } while(gui.pollCallback(callback)){
                if(callback.id==1){(client.manager).sendRawPacket(&client.socket, rha::typePacketsInClient::QUESTION_CLIENT_JOIN);} //todo
                else if(callback.id==2){client.disconnect(); state=MENU; break;}
            }

            client.updateAll(window);
        }

        window.clear(sf::Color(41, 137, 216));
        client.drawAll(window);
        window.setView(client.getView());
        window.draw(title);
        window.setView(window.getDefaultView());
        gui.draw();
        window.display();
    }
}

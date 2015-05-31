#include "gameManager.hpp"

rha::cGameManager::cGameManager(sf::Vector2i size, std::string title){
    window.create(sf::VideoMode(size.x, size.y, 32), title, sf::Style::Close);
    if(!cManagerResources::getObj().isLoaded()){
        std::cout<<"Error: Loading resources failed!\n";

        state=END; //todo - logger
    } else{gui.setGlobalFont(*cManagerResources::getObj().getFont()); state=MENU;}
} void rha::cGameManager::manageApp(){
    while(window.isOpen()){
        switch(state){
            case MENU:
              this->sMenu();
               break;
            case GAME:
              this->sRunning();
               break;
            case END:
              window.close();
               break;
        }
    }
}

/*-------------*/

void rha::cGameManager::sMenu(){
    std::thread thrConnect;

    gui.removeAllWidgets();
    gui.loadWidgetsFromFile("media/oldStyle/menuForm.RhAf");

    while(state==MENU){
        if(client.getStatus()==cClient::WATCHING||client.getStatus()==cClient::PLAYING) state=GAME;
        while(window.pollEvent(event)){
            switch(event.type){
             case sf::Event::Closed:
                state=END; break;

                //...
            }

            gui.handleEvent(event);
        } while(gui.pollCallback(callback)){
            switch(callback.id){
                case 1:{
                  tgui::EditBox::Ptr eBoxCopy1=gui.get("EditBox1");
                  tgui::EditBox::Ptr eBoxCopy2=gui.get("EditBox2");

                   std::string text1=eBoxCopy1->getText(), text2=eBoxCopy2->getText();
                  thrConnect=std::thread(&rha::cClient::connect, &client,
                   text1, 7415, text2); thrConnect.detach(); break;
                }
                case 2: state=END; break;
            }
        }

        window.clear();
         gui.draw();
        window.display();
    }
}

void rha::cGameManager::sRunning(){
    sf::Clock clock; sf::Time time;
    sf::Time timeOfUpdate=sf::Time::Zero;
    const sf::Time timeStep=sf::seconds(1/60.f);

    gui.removeAllWidgets();
    gui.loadWidgetsFromFile("media/oldStyle/gameForm.RhAf");

    while(state==GAME){
        time=clock.restart();

        timeOfUpdate+=time;
        while(timeOfUpdate>timeStep){
            timeOfUpdate-=timeStep;

            if(client.getStatus()==cClient::eStatus::NOTCONNECT) state=MENU;
            while(window.pollEvent(event)){
                client.managePlayer(event);

                gui.handleEvent(event);
            } while(gui.pollCallback(callback)){
                switch(callback.id){
                    case 1: (client.manager).sendRawPacket(&client.socket, rha::typePacketsInClient::QUESTION_CLIENT_JOIN); break;
                    case 2: client.disconnect(); state=MENU; break;
                }
            }

            client.updateAll(window);
        }

        window.clear(sf::Color(41, 137, 216));
         client.drawAll(window);

         gui.draw();
        window.display();
    }
}

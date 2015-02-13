#include "gameManager.hpp"

rha::cGameManager::cGameManager(sf::Vector2i size, std::string title){
    window.create(sf::VideoMode(size.x, size.y, 32), title, sf::Style::Close);
    if(!font.loadFromFile("media/font.ttf")){
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
    gui.setGlobalFont(font);
    loaderGUI.loadMenuGUI(gui);

    sf::Text title("Hammerfall", font, 50); //todo - logo.
    title.setOrigin(title.getGlobalBounds().width/2, 50/2);
    title.setPosition((window.getSize()).x/2, 75);

    std::string choices[]={"Play", "Quit"};
    sf::Text txChoices[2];
    for(short i=0; i<2; ++i){ //todo - delete, author's manager sf::Text
        txChoices[i].setFont(font);
        txChoices[i].setString(choices[i]);
        txChoices[i].setCharacterSize(30);

        txChoices[i].setOrigin(txChoices[i].getGlobalBounds().width/2, 30/2);
        txChoices[i].setPosition((window.getSize()).x/2,250+i*60);
    }

    sf::Event event;
    while(state==MENU){
        if(client.getConnect()) state=GAME;
        mouse=static_cast<sf::Vector2f>(sf::Mouse::getPosition(window));
        while(window.pollEvent(event)){
            switch(event.type){
             case sf::Event::Closed:
                state=END; break;
             case sf::Event::MouseButtonReleased:
                if((event.key).code==sf::Mouse::Left){
                    if((txChoices[0].getGlobalBounds()).contains(mouse)){
                        std::thread thrConnect(&rha::cClient::connect, &client, "localhost", 7415); thrConnect.detach();
                    } else if((txChoices[1].getGlobalBounds()).contains(mouse)){
                        state=END;
                    }
                }
             default: break;
            }
            gui.handleEvent(event);
        }

        for(short i=0; i<2; ++i){ //todo - delete this code, author's manager sf::Text.
            if((txChoices[i].getGlobalBounds()).contains(mouse))
                txChoices[i].setColor(sf::Color::Red);
            else txChoices[i].setColor(sf::Color::White);
        }

        window.clear();
        window.draw(title);
        for(short i=0; i<2; ++i) //todo - delete this code.
         window.draw(txChoices[i]);
         gui.draw();

        window.display();
    }
}

void rha::cGameManager::runGame(){
    sf::Text title("Game is create...", font, 50); //only test
    title.setOrigin(title.getGlobalBounds().width/2, 50/2);
    title.setPosition((window.getSize()).x/2, 75);

    sf::Event event;
    while(state==GAME){
        while(window.pollEvent(event)){
            switch(event.type){
             case sf::Event::Closed:
                client.disconnect(); state=MENU; break;
             default: break;
            }
        }

        //...

        window.clear();
        window.draw(title);

        window.display();
    }
}

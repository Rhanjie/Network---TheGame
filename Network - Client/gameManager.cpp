#include "gameManager.hpp"

rha::cGameManager::cGameManager(sf::Vector2i size, std::string title){
    window.create(sf::VideoMode(size.x, size.y, 32), title, sf::Style::Close);
    if(!font.loadFromFile("media/font.ttf")){
        state=END; return;
    } else state=MENU;
} void rha::cGameManager::runGame(){
    while(window.isOpen()){
        switch(state){
            case MENU:
             this->menu(); break;
            case GAME:
             /*...*/ break;
            case END:
             window.close(); break;
        }
    }
}

/*-------------*/

void rha::cGameManager::menu(){
    sf::Text title("Network - Client", font, 50);
    title.setOrigin(title.getGlobalBounds().width/2, 50/2);
    title.setPosition(800/2, 75);

    //...

    //client.connect("localhost", 7415); //todo

    while(state==MENU){
        rha::checkEvent(&window, &event); //temporary

        window.clear();

        window.draw(title);
        window.display();
    }
}

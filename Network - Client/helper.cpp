#include "helper.hpp"

void rha::checkEvent(sf::Window* window, sf::Event* event){
    while(window->pollEvent(*event)){
        switch(event->type){
         case sf::Event::Closed:
            window->close(); break;
         case sf::Event::KeyPressed:
            if(event->key.code==sf::Keyboard::Escape)
                window->close(); break;
         default: break;
        }
    }
}

#include "helper.hpp"

void rha::checkEvent(sf::Window* window, sf::Event* event){ //todo
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

bool rha::checkPhrase(std::string text, std::string phrase){
    size_t searched_phrase=text.find(phrase);
    if(searched_phrase==std::string::npos){
        return false;
    }else return true;
}


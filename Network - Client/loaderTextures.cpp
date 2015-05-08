#include "loaderTextures.hpp"

void rha::cManagerResources::loadAll(){
    sf::Texture texture;

    if(!font.loadFromFile("media/font.ttf")) loaded=false;

    //...
    for(int i=0; i<2; ++i){ //profession
        for(int j=0; j<2; ++j){ //team color
            std::string helper="media/player "+tgui::to_string(i+1)
             +tgui::to_string(j+1)+".png"; //todo - test

            if(texture.loadFromFile(helper))
             vTextures.push_back(texture);
            else loaded=false;
        }
    }

    if(texture.loadFromFile("media/tiles01.png")) //todo - test
     vTextures.push_back(texture);
    else loaded=false;
}

#include "loaderTextures.hpp"

void rha::cManagerResources::loadAll(){
    sf::Texture texture; std::string helper;

    if(!font.loadFromFile("media/font.ttf")){loaded=false; return;}

    //...
    for(int i=0; i<2; ++i){ //profession
        for(int j=0; j<2; ++j){ //team color
            helper="media/player "+tgui::to_string(i+1)+tgui::to_string(j+1)+".png";

            if(texture.loadFromFile(helper))
             vTextures.push_back(texture);
            else{loaded=false; return;}
        }
    }

    if(texture.loadFromFile("media/tiles01.png")) //todo - test
     vTextures.push_back(texture);
    else loaded=false;
}

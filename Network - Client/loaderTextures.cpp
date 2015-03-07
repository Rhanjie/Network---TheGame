#include "loaderTextures.hpp"

void rha::cLoaderTexture::loadAll(){
    sf::Texture texture;

    for(int i=0; i<2; ++i){
        std::string helper="media/Hammerdwarf"+tgui::to_string(i+1)+".png"; //todo - test

        if(texture.loadFromFile(helper));
         vTextures.push_back(texture);
    }
}

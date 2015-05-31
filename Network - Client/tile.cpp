#include "tile.hpp"

rha::cTile::cTile(sf::Sprite* sprite){
    this->sprite=sprite;

    //...
}

void rha::cTileManager::setTextures(eStyle style){
    sf::Sprite sprite; unsigned short x=0, y=0;

    sprite=(cManagerResources::getObj()).getGraph(4+int(style));
    for(int i=0; i<((((sprite.getTexture())->getSize()).x/w)*(((sprite.getTexture())->getSize().y)/h)); ++i){
        vSprites.push_back(sf::Sprite());

        y=i/((sprite.getTexture())->getSize().x/w);
        x=i%((sprite.getTexture())->getSize().x/w);
        sprite.setTextureRect(sf::IntRect(x*w, y*h, w, h));
        sprite.setOrigin(w/2,h/2);

        vSprites[vSprites.size()-1]=sprite;
    }
}

#include "textureAnimation.hpp"

//rha::cTextureAnimation::cTextureAnimation(std::string path, sf::Vector2i sizeFrame){setOtherTexture(path, sizeFrame);}
void rha::cTextureAnimation::setOtherTexture(sf::Sprite sprite, sf::Vector2i sizeFrame){
    this->sizeFrame=sizeFrame;

    this->sprite=sprite;
    this->texture=*this->sprite.getTexture();

    quantityFrame.x=(this->sprite.getTexture())->getSize().x/this->sizeFrame.x;
    quantityFrame.y=(this->sprite.getTexture())->getSize().y/this->sizeFrame.y;
    currentFrame=sf::Vector2i(0,0);

    sprite.setTextureRect(sf::IntRect(currentFrame.x*this->sizeFrame.x, currentFrame.y*this->sizeFrame.y,
     (currentFrame.x*this->sizeFrame.x)+this->sizeFrame.x, (currentFrame.y*this->sizeFrame.y)+this->sizeFrame.y));
    sprite.setOrigin(sizeFrame.x/2, sizeFrame.y/2);
}

void rha::cTextureAnimation::serveAnimation(){
    currentFrame.x+=1; //60 = 1 second

    sprite.setTextureRect(sf::IntRect(currentFrame.x/30*this->sizeFrame.x,
     currentFrame.y*this->sizeFrame.y, this->sizeFrame.x, this->sizeFrame.y));
    if(currentFrame.x>=30*quantityFrame.x) currentFrame.x=0;
}

void rha::cTextureAnimation::setAnimation(short int y){
    if(y>quantityFrame.y) y=quantityFrame.y; currentFrame.y=y;

    currentFrame.x=0;
}

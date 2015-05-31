#include "textureAnimation.hpp"

void rha::cTextureAnimation::setOtherTexture(sf::Sprite sprite){
    this->sprite=sprite; this->texture=*this->sprite.getTexture();

    currentFrame=sf::Vector2i(0,0);
}

void rha::cTextureAnimation::serveAnimation(){
    currentFrame.x+=3; //60 = 1 second

    if(currentFrame.x>=30*quantityFrame.x) currentFrame.x=0;
    sprite.setTextureRect(sf::IntRect(currentFrame.x/30*this->sizeFrame.x,
     currentFrame.y*this->sizeFrame.y, this->sizeFrame.x, this->sizeFrame.y));
}


void rha::cTextureAnimation::setSizeFrame(sf::Vector2i sizeFrame){
    this->sizeFrame=sizeFrame;

    quantityFrame.x=(this->sprite.getTexture())->getSize().x/this->sizeFrame.x;
    quantityFrame.y=(this->sprite.getTexture())->getSize().y/this->sizeFrame.y;

    sprite.setTextureRect(sf::IntRect(currentFrame.x*this->sizeFrame.x, currentFrame.y*this->sizeFrame.y,
     (currentFrame.x*this->sizeFrame.x)+this->sizeFrame.x, (currentFrame.y*this->sizeFrame.y)+this->sizeFrame.y));
    sprite.setOrigin(sizeFrame.x/2, sizeFrame.y/2);
}

void rha::cTextureAnimation::setAnimation(unsigned short int y){
    if(y>quantityFrame.y)y=quantityFrame.y;
     currentFrame.y=y; currentFrame.x=0;

    this->serveAnimation();
}

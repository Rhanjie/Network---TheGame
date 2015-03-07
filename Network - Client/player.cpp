#include "player.hpp"

rha::cPlayer::cPlayer(){
    cBasePerson();

    x=y=vY=regX=regY=inAir=0; hp=1;

    vX=1; //todo - test
    view.setCenter(x, y);
    textureTest.loadFromFile("media/Hammerdwarf1.png");
    sf::Sprite sprite; sprite.setTexture(textureTest);
    textureAnimation.setOtherTexture(sprite, sf::Vector2i(20, 20)); //loaderTexture.getTexture(0)
    action=STAND; direction=RIGHT;
    team=NONE; profession=LACK;
    view.zoom(0.5);
}
void rha::cPlayer::spawn(sf::Int32 x, sf::Int32){
    action=STAND; direction=RIGHT;

    regX=x, regY=y;
    this->x=x, this->y=y;
    view.setCenter(this->x, this->y);

    (textureAnimation.sprite).setPosition(this->x, this->y);

    //...
}


void rha::cPlayer::performAction(){
    sf::Time timer;

    switch(action){
        case STAND: break;
        case MOVE: moveUp(); break;
        case JUMP: break;
        case ATTACK: break;
    } textureAnimation.serveAnimation();
}

void rha::cPlayer::setTeam(eTeam team){this->team=team;}
void rha::cPlayer::setProfession(eProfession profession){this->profession=profession;}
void rha::cPlayer::setAction(eAction action){this->action=action;}
void rha::cPlayer::setDirection(eDirection direction){this->direction=direction;}
/*****private*****/

void rha::cPlayer::moveUp(){
    if(direction==cPlayer::LEFT)x+=vX;
    else if(direction==cPlayer::RIGHT)x-=vX;

    (view).setCenter(x, y);
    (textureAnimation.sprite).setPosition(x, y);
}

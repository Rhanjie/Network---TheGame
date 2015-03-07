#include "otherPlayers.hpp"

rha::cOtherPlayer::cOtherPlayer(std::string nick, sf::Sprite sprite){
    cBasePerson();

    this->nick=nick;
    x=y=vY=regX=regY=inAir=0; hp=1; //todo

    vX=1; //todo - test
    std::cout<<"Add new otherClient - "<<nick<<std::endl;
    action=STAND; direction=RIGHT;
    team=NONE; profession=LACK;

    textureAnimation.setOtherTexture(sprite, sf::Vector2i(20, 20));
}

void rha::cOtherPlayer::performAction(){
    switch(action){
        case STAND: break;
        case MOVE: moveUp(); break;
        case JUMP: break;
        case ATTACK: break;
    } textureAnimation.serveAnimation();
}

/*****private*****/
void rha::cOtherPlayer::moveUp(){
    if(direction==eDirection::LEFT) x+=vX;
    else if(direction==eDirection::RIGHT) x-=vX;
    (textureAnimation.sprite).setPosition(x, y);
}

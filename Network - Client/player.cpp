#include "player.hpp"

rha::cPlayer::cPlayer(){
    cBasePerson();

    x=y=vY=regX=regY=0; hp=100;
    inAir=0; vX=1; //todo - test

    view.setCenter(x, y); view.setSize(800,600); //todo - global option, window size
    textureAnimation.setOtherTexture((cManagerResources::getObj()).getGraph(2), sf::Vector2i(40, 40));
    //(textureAnimation.sprite).setOrigin((textureAnimation.sprite).getGlobalBounds().height);
    textureAnimation.setAnimation(0);

    action=STAND; direction=RIGHT;
    team=NONE; profession=LACK;
    view.zoom(0.5);
}
void rha::cPlayer::spawn(sf::Int32 x, sf::Int32 y){ //todo
    action=STAND; direction=RIGHT;

    regX=x, regY=y;
    this->x=x, this->y=y;
    view.setCenter(this->x, this->y);

    (textureAnimation.sprite).setPosition(this->x, this->y);

    //...
}


void rha::cPlayer::performAction(){
    switch(action){
        case STAND: break;
        case MOVE: moveUp(); break;
        case JUMP: break;
        case ATTACK: break;
    } if(action!=STAND)
     textureAnimation.serveAnimation();
}

void rha::cPlayer::setTeam(eTeam team){this->team=team;}
void rha::cPlayer::setProfession(eProfession profession){this->profession=profession;}
void rha::cPlayer::setAction(eAction action){this->action=action;}
void rha::cPlayer::setDirection(eDirection direction){this->direction=direction;}

/*****private*****/
void rha::cPlayer::moveUp(){
    if(direction==cPlayer::LEFT)x-=vX;
    else if(direction==cPlayer::RIGHT)x+=vX;

    (textureAnimation.sprite).setPosition(x, y);
    view.setCenter(x, y);
}

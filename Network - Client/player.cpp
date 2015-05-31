#include "player.hpp"

rha::cPlayer::cPlayer(){
    cBasePerson();

    /*todo - test*/
    x=y=vY=regX=regY=0;
    hp=100; inAir=0; vX=1;
    /*...........*/

    view.setCenter(x, y); view.setSize(800,600); view.zoom(0.5); //todo - global option, window size

    textureAnimation.setOtherTexture((cManagerResources::getObj()).getGraph(2)); //todo - class
    short w=((textureAnimation.sprite).getTexture())->getSize().x/3;
    short h=((textureAnimation.sprite).getTexture())->getSize().y/5;

    textureAnimation.setSizeFrame(sf::Vector2i(w, h));
    textureAnimation.setAnimation(0);

    /*(textureAnimation.sprite).setOrigin(w, h);*/ //todo - collision box.

    action=STAND; direction=RIGHT;
    team=NONE; profession=LACK;
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

void rha::cPlayer::spawn(sf::Int32 x, sf::Int32 y){ //todo
    action=STAND; direction=RIGHT;

    regX=x, regY=y;
    this->x=regX, this->y=regY;
    view.setCenter(this->x, this->y);

    (textureAnimation.sprite).setPosition(this->x, this->y);

    //...
}

/*****private*****/
void rha::cPlayer::moveUp(){
    if(direction==cPlayer::LEFT)x-=vX;
    else if(direction==cPlayer::RIGHT)x+=vX;

    (textureAnimation.sprite).setPosition(x, y);
       view.setCenter(x, y);
}


void rha::cPlayer::setTeam(eTeam team){this->team=team;}
void rha::cPlayer::setProfession(eProfession profession){this->profession=profession;}
void rha::cPlayer::setAction(eAction action){this->action=action;}
void rha::cPlayer::setDirection(eDirection direction){this->direction=direction;}

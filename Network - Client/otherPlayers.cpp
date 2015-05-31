#include "otherPlayers.hpp"

rha::cOtherPlayer::cOtherPlayer(std::string nick, sf::Sprite sprite){
    cBasePerson();

    this->nick=nick;

    /*todo - test*/
    x=y=vY=regX=regY=inAir=0; hp=vX=1;
    action=STAND; direction=RIGHT;
    team=NONE; profession=LACK;

    std::cout<<"Add new otherClient - "<<nick<<std::endl;
    /*...........*/

    textureAnimation.setOtherTexture(sprite);
    short w=((textureAnimation.sprite).getTexture())->getSize().x/3;
    short h=((textureAnimation.sprite).getTexture())->getSize().y/5;

    textureAnimation.setSizeFrame(sf::Vector2i(w, h));
    textureAnimation.setAnimation(0); //setText();
    (textureAnimation.sprite).setPosition(x, y);
}

void rha::cOtherPlayer::performAction(){
    switch(action){
        case STAND: break;
        case MOVE: moveUp(); break;
        case JUMP: break;
        case ATTACK: break;
    } if(action!=STAND)
    textureAnimation.serveAnimation();
}

void rha::cOtherPlayer::addToGame(float x, float y, eTeam team, eProfession profession){
    setStatus(cOtherPlayer::eStatus::PLAYING);

    this->x=x; this->y=y; this->team=team;
    this->profession=profession;
}

/*****private*****/
/*void rha::cOtherPlayer::setText(){ //todo
    sf::FloatRect rect=text.getGlobalBounds();

    text.setFont(*cManagerResources::getObj().getFont());
    text.setString(this->nick); text.setCharacterSize(10);
    text.setOrigin(rect.left+rect.width/2.f,rect.top+rect.height/2.f);
    text.setPosition((textureAnimation.sprite).getPosition());
}*/
void rha::cOtherPlayer::moveUp(){
    if(direction==eDirection::LEFT) x-=vX;
    else if(direction==eDirection::RIGHT) x+=vX;

    (textureAnimation.sprite).setPosition(x, y);
    //text.setPosition((textureAnimation.sprite).getPosition());
}

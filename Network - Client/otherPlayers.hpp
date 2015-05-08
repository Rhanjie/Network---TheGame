#ifndef OTHERPLAYERS_HPP_INCLUDED
#define OTHERPLAYERS_HPP_INCLUDED
#include "loaderTextures.hpp"
#include "managerLibs.hpp"
#include "basePerson.hpp"

namespace rha{
    class cOtherPlayer :public cBasePerson{
        friend cBasePerson;
        public:
         enum eStatus{WATCHING, PLAYING};
        private:
         eStatus status;
         //sf::Text text;

         void setText();
         void stand();
         void moveUp();
         void jump();
        public:
         cOtherPlayer(std::string nick, sf::Sprite sprite);
         void performAction();

         void setStatus(eStatus status){this->status=status;}
         inline eStatus getStatus(){return status;}

         sf::Text text; //todo - test
    };
}

#endif // OTHERPLAYERS_HPP_INCLUDED

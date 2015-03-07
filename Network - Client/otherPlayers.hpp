#ifndef OTHERPLAYERS_HPP_INCLUDED
#define OTHERPLAYERS_HPP_INCLUDED
#include "managerLibs.hpp"
#include "basePerson.hpp"

namespace rha{
    class cOtherPlayer :public cBasePerson{
        friend cBasePerson;
        public:
         cOtherPlayer(std::string nick, sf::Sprite sprite);
         void performAction();
        private:
         void stand();
         void moveUp();
         void jump();
    };
}

#endif // OTHERPLAYERS_HPP_INCLUDED

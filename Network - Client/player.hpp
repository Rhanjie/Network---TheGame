#ifndef PLAYER_HPP_INCLUDED
#define PLAYER_HPP_INCLUDED
#include "managerLibs.hpp"
#include "basePerson.hpp"

namespace rha{
    class cPlayer :public cBasePerson{
        friend cBasePerson;
        public:
         sf::View view;
         cTextureAnimation textureAnimation; sf::Texture textureTest;
         sf::Clock clock;

         cPlayer();
         void spawn(sf::Int32 x, sf::Int32 y);
         void setTeam(eTeam team);
         void setProfession(eProfession profession);
         void setAction(eAction action);
         void setDirection(eDirection direction);

         void performAction();
        private:
         void stand();
         void moveUp();
         void jump();
    };
}

#endif // PLAYER_HPP_INCLUDED

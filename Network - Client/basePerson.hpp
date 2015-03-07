#ifndef BASEPERSON_HPP_INCLUDED
#define BASEPERSON_HPP_INCLUDED
#include "managerLibs.hpp"
#include "textureAnimation.hpp"

namespace rha{
    class cBasePerson{
        public:
         enum eTeam{GREEN, ORANGE, NONE};
         enum eProfession{HAMMERDWARF, SPEARMAN, DAGGERELF, LACK};
         enum eAction{STAND, MOVE, JUMP, ATTACK};
         enum eDirection{LEFT, RIGHT};
         cTextureAnimation textureAnimation;
        public: //protected:
         eTeam team; eProfession profession;
         eAction action; eDirection direction;

         std::string nick;
         float x, y; float vX, vY;
         sf::Int32 regX, regY;

         bool inAir; sf::Int8 hp;
        public:
         inline eTeam getTeam(){return team;}
         inline eProfession getProfession(){return profession;}
         inline eAction getAction(){return action;}
         inline eDirection getDirection(){return direction;}
    };
}

#endif // BASEPERSON_HPP_INCLUDED

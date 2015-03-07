#ifndef PLAYER_HPP_INCLUDED
#define PLAYER_HPP_INCLUDED
#include "managerLibs.hpp"

namespace rha{
    class cPlayer{
        public:
         enum eTeam{GREEN, ORANGE, NONE};
         enum eProfession{HAMMERDWARF, SPEARMAN, DAGGERELF, LACK};
         enum eAction{STAND, MOVE, JUMP, ATTACK};
         enum eDirection{LEFT, RIGHT};
        public: //private:
         sf::Int32 x, y; float vX, vY;
         bool inAir; sf::Int8 hp;
        public:
         cPlayer();

         eTeam team; eProfession profession;
         eAction action; eDirection direction;

         inline sf::Int32 getVx(){return vX;}
    };
}

#endif // PLAYER_HPP_INCLUDED

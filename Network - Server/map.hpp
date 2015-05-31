#ifndef MAP_HPP_INCLUDED
#define MAP_HPP_INCLUDED
#include "managerLibs.hpp"

namespace rha{
    class cMap{
        private:
         sf::Vector2u size;
         bool loaded=false;
        public:
         cMap(); //create default map 0x0
         void setSize(sf::Vector2u size);
         inline sf::Vector2u getSize(){return size;}

         unsigned short **arrFront;
         unsigned short **arrBack;
    };
}

#endif // MAP_HPP_INCLUDED

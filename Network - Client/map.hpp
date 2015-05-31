#ifndef MAP_HPP_INCLUDED
#define MAP_HPP_INCLUDED
#include "managerLibs.hpp"
#include "tile.hpp"

namespace rha{
    class cMap{
        private:
         sf::Vector2u size;
         cTileManager tileManager;

         unsigned short **arrFront;
         unsigned short **arrBack;
         std::vector<cTile>vTiles;
        public:
         cMap(); //create default map 0x0
         void setSize(sf::Packet& packet);
         void draw(sf::RenderWindow& window);
         void setTiles(unsigned short X=0, unsigned short Y=0,
            unsigned short W=0, unsigned short H=0);
    };
}

#endif // MAP_HPP_INCLUDED

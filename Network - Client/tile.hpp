#ifndef TILE_HPP_INCLUDED
#define TILE_HPP_INCLUDED
#include "loaderTextures.hpp"
#include "managerLibs.hpp"

namespace rha{
    class cTile{
        private:
         sf::Sprite* sprite;

         unsigned short id;
          bool collision=false;
          unsigned short angle=0;
        public:
         cTile(sf::Sprite* sprite);

         void setAngle(unsigned short angle){this->angle=angle;}
         inline sf::Sprite* getSprite(){return sprite;}
         inline unsigned short getAngle(){return angle;}
    };

    class cTileManager{
        public:
         enum eStyle{WINTER};
        private:
         short w=16, h=16;

         std::vector<sf::Sprite>vSprites;
        public:
         void setTextures(eStyle style);
         void draw(sf::RenderWindow* target);

         inline sf::Sprite* getIndicatedSprite(unsigned short i){return &vSprites[i];}
         inline unsigned short getSizeVectorSprites(){return vSprites.size();}
    };
}

#endif // TILE_HPP_INCLUDED

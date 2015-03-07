#ifndef TEXTUREANIMATION_HPP_INCLUDED
#define TEXTUREANIMATION_HPP_INCLUDED
#include "managerLibs.hpp"

namespace rha{
    class cTextureAnimation{
        public:
         sf::Vector2i sizeFrame;
         sf::Vector2i currentFrame;
         sf::Vector2i quantityFrame;

         sf::Texture texture;
         sf::Sprite sprite;

         void serveAnimation();
         void setOtherTexture(sf::Sprite sprite, sf::Vector2i sizeFrame);

         inline sf::Sprite getGraph(){return sprite;}
         void setAnimation(short int y);
    };
}

#endif // TEXTUREANIMATION_HPP_INCLUDED

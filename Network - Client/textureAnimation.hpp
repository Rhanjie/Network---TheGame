#ifndef TEXTUREANIMATION_HPP_INCLUDED
#define TEXTUREANIMATION_HPP_INCLUDED
#include "managerLibs.hpp"

namespace rha{
    class cTextureAnimation{
        public:
         sf::Vector2i sizeFrame, currentFrame, quantityFrame;
         sf::Texture texture; sf::Sprite sprite;

         void serveAnimation();

         void setOtherTexture(sf::Sprite sprite);
         void setSizeFrame(sf::Vector2i sizeFrame);
         void setAnimation(unsigned short int y);

         inline sf::Sprite getGraph(){return sprite;}
    };
}

#endif // TEXTUREANIMATION_HPP_INCLUDED

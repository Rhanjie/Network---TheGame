#ifndef LOADERTEXTURES_HPP_INCLUDED
#define LOADERTEXTURES_HPP_INCLUDED
#include "managerLibs.hpp"

namespace rha{
    class cLoaderTexture{
        private:
         std::vector<sf::Texture>vTextures;
         void loadAll(); //fill the std::vector
        public:
         cLoaderTexture(){loadAll();}
         ~cLoaderTexture(){vTextures.clear();}

         inline sf::Sprite getGraph(short i){
            sf::Sprite spriteHelper;

            if(i<vTextures.size())
             spriteHelper.setTexture(vTextures[i]);
            return spriteHelper;
         }
    };
}

#endif // LOADERTEXTURES_HPP_INCLUDED

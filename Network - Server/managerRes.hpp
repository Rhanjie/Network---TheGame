#ifndef LOADERTEXTURES_HPP_INCLUDED
#define LOADERTEXTURES_HPP_INCLUDED
#include "managerLibs.hpp"

namespace rha{
    class cManagerResources{
        private:
         cManagerResources(){loadAll();}
         cManagerResources(const cManagerResources&);
         ~cManagerResources(){vTextures.clear();}

         sf::Font font; bool loaded=true;
         std::vector<sf::Texture>vTextures;

         void loadAll(); //fill the std::vector
        public:
         static cManagerResources& getObj(){
            static cManagerResources resObject;

            return resObject;
         }

         inline bool isLoaded(){return loaded;}
         inline sf::Font* getFont(){return &font;} //get pointer to the object.
         inline sf::Sprite getGraph(unsigned short i){ //get copy an object.
            sf::Sprite spriteHelper;

            if(i<vTextures.size())
             spriteHelper.setTexture(vTextures[i]);
            return spriteHelper;
         }
    };
}

#endif // LOADERTEXTURES_HPP_INCLUDED

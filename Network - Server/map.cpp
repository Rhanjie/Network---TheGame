#include "map.hpp"

rha::cMap::cMap(){
    //tileManager.setTextures(cTileManager::eStyle::WINTER);

    size=sf::Vector2u(0,0);
    arrFront=new unsigned short*[size.y];
    arrBack=new unsigned short*[size.y];

    for(unsigned short i=0; i<size.y; ++i){
        arrFront[i]=new unsigned short[size.x];
        arrBack[i]=new unsigned short[size.x];
    }

    for(int y=0; y<size.y; ++y){
        for(int x=0; x<size.x; ++x){
            arrFront[y][x]=0;
            arrBack[y][x]=0;
        }
    }
}

void rha::cMap::setSize(sf::Vector2u size){
    for(unsigned short i=0; i<this->size.y; ++i){
        delete[] arrFront[i]; delete[] arrBack[i];
    } delete[] arrFront; delete[] arrBack;

    this->size.x=size.x; this->size.y=size.y;
    arrFront=new unsigned short*[this->size.y];
    arrBack=new unsigned short*[this->size.y];

    for(unsigned short i=0; i<this->size.y; ++i){
        arrFront[i]=new unsigned short[this->size.x];
        arrBack[i]=new unsigned short[this->size.x];
    }

    for(int y=0; y<this->size.y; ++y){
        for(int x=0; x<this->size.x; ++x){
            //todo - load map from file
            arrFront[y][x]=(rand()%3)+1;
        }
    }

    loaded=true;
}

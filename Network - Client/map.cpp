#include "map.hpp"

rha::cMap::cMap(){
    tileManager.setTextures(cTileManager::eStyle::WINTER);

    size=sf::Vector2u(0,0);
    arrFront=new unsigned short*[size.y];
    arrBack=new unsigned short*[size.y];
    for(unsigned short i=0; i<size.y; ++i){
        arrFront[i]=new unsigned short[size.x];
        arrBack[i]=new unsigned short[size.x];
    }

    for(int y=0; y<size.y; ++y){
        for(int x=0; x<size.x; ++x){
            arrFront[y][x]=arrBack[y][x]=0;
        }
    }

    this->setTiles();
}

void rha::cMap::setSize(sf::Packet& packet){
    unsigned short helper=0; sf::Vector2u newSize;

    if(packet>>newSize.x>>newSize.y){
        for(unsigned short i=0; i<size.y; ++i){
         delete[] arrFront[i]; delete[] arrBack[i];
        } delete[] arrFront; delete[] arrBack;

        size.x=newSize.x; size.y=newSize.y;
        arrFront=new unsigned short*[size.y];
        arrBack=new unsigned short*[size.y];
        for(unsigned short i=0; i<size.y; ++i){
            arrFront[i]=new unsigned short[size.x];
            arrBack[i]=new unsigned short[size.x];
        }

        for(int y=0; y<size.y; ++y){
            for(int x=0; x<size.x; ++x){
                packet>>helper; arrFront[y][x]=helper;
                packet>>helper; arrBack[y][x]=helper;
            }
        } this->setTiles();
    } else{std::cout<<"Packet (MAP) error!\n";}
}

void rha::cMap::draw(sf::RenderWindow& window){
    unsigned short which=0; //y*x

    for(int y=0; y<size.y; ++y){
        for(int x=0; x<size.x; ++x){
            (vTiles[which].getSprite())->setRotation(vTiles[which].getAngle());
            (vTiles[which].getSprite())->setPosition(x*16, y*16);
            window.draw(*vTiles[which].getSprite());

            which+=1;
        }
    }
}

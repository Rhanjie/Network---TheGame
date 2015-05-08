#include "map.hpp"

rha::cMap::cMap(){
    tileManager.setTextures(cTileManager::eStyle::WINTER);
    arrFront=new unsigned short*[h];
    arrBack=new unsigned short*[h];
    for(unsigned short i=0; i<h; ++i){
        arrFront[i]=new unsigned short[w];
        arrBack[i]=new unsigned short[w];
    }

    for(int y=0; y<h; ++y){
        for(int x=0; x<w; ++x){
            arrFront[y][x]=0;
            arrBack[y][x]=0;
        }
    }

    this->setTiles();
}

void rha::cMap::setSize(sf::Packet& packet){
    unsigned short newW=10, newH=10; short helper;

    //if(packet>>newW>>newH){
    {
        std::cout<<"WH size map: "<<newW<<", "<<newH<<std::endl;
        for(unsigned short i=0; i<h; ++i){
         delete[] arrFront[i]; delete[] arrBack[i];
        } delete[] arrFront; delete[] arrBack;

        w=newW; h=newH;
        arrFront=new unsigned short*[h];
        arrBack=new unsigned short*[h];
        for(unsigned short i=0; i<h; ++i){
            arrFront[i]=new unsigned short[w];
            arrBack[i]=new unsigned short[w];
        }

        for(int y=0; y<h; ++y){
            for(int x=0; x<w; ++x){
                /*helper<<packet;
                arrFront[y][x]=helper;*/
                if(y>1)arrFront[y][x]=2;
                else arrFront[y][x]=1;
            }
        }

        //debug - only test.
        arrFront[5][5]=3; arrFront[5][6]=3;
        arrFront[6][5]=3; arrFront[6][6]=3;
        arrFront[7][6]=0; arrFront[7][7]=0;
        this->setTiles();
    }
}

void rha::cMap::draw(sf::RenderWindow& window){
    unsigned short which=0; //y*x

    for(int y=0; y<h; ++y){
        for(int x=0; x<w; ++x){
            (vTiles[which].getSprite())->setRotation(vTiles[which].getAngle());
            (vTiles[which].getSprite())->setPosition(x*16, y*16);
            window.draw(*vTiles[which].getSprite());

            which+=1;
        }
    }
}

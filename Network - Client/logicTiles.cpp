#include "map.hpp"

void rha::cMap::setTiles(unsigned short X, unsigned short Y,
     unsigned short W, unsigned short H){
    if(!vTiles.empty()) vTiles.clear();

    for(int y=0; y<this->h; ++y){
        for(int x=0; x<this->w; ++x){
            if(arrFront[y][x]>0){
                //other cases

                if((y>0&&x<this->w-1&&arrFront[y-1][x]==arrFront[y][x]&&arrFront[y][x+1]==arrFront[y][x]&&arrFront[y-1][x+1]!=arrFront[y][x])||
                  (y<this->h-1&&x<this->w-1&&arrFront[y+1][x]==arrFront[y][x]&&arrFront[y][x+1]==arrFront[y][x]&&arrFront[y+1][x+1]!=arrFront[y][x])||
                 (y<this->h-1&&x>0&&arrFront[y+1][x]==arrFront[y][x]&&arrFront[y][x-1]==arrFront[y][x]&&arrFront[y+1][x-1]!=arrFront[y][x])||
                (y>0&&x>0&&arrFront[y-1][x]==arrFront[y][x]&&arrFront[y][x-1]==arrFront[y][x]&&arrFront[y-1][x-1]!=arrFront[y][x])){
                    vTiles.push_back(tileManager.getIndicatedSprite((rand()%3)+(((arrFront[y][x]-1)*18)+9)));

                    if((y>0&&x<this->w-1&&arrFront[y-1][x]==arrFront[y][x]&&arrFront[y][x+1]==arrFront[y][x]&&arrFront[y-1][x+1]!=arrFront[y][x])) vTiles[vTiles.size()-1].setAngle(0);
                    else if((y<this->h-1&&x<this->w-1&&arrFront[y+1][x]==arrFront[y][x]&&arrFront[y][x+1]==arrFront[y][x]&&arrFront[y+1][x+1]!=arrFront[y][x])) vTiles[vTiles.size()-1].setAngle(90);
                    else if((y<this->h-1&&x>0&&arrFront[y+1][x]==arrFront[y][x]&&arrFront[y][x-1]==arrFront[y][x]&&arrFront[y+1][x-1]!=arrFront[y][x])) vTiles[vTiles.size()-1].setAngle(180);
                    else if((y>0&&x>0&&arrFront[y-1][x]==arrFront[y][x]&&arrFront[y][x-1]==arrFront[y][x]&&arrFront[y-1][x-1]!=arrFront[y][x])) vTiles[vTiles.size()-1].setAngle(270);

                } else if((y>0&&x<this->w-1&&arrFront[y-1][x]!=arrFront[y][x]&&arrFront[y][x+1]!=arrFront[y][x])||
                  (y<this->h-1&&x<this->w-1&&arrFront[y+1][x]!=arrFront[y][x]&&arrFront[y][x+1]!=arrFront[y][x])||
                 (y<this->h-1&&x>0&&arrFront[y+1][x]!=arrFront[y][x]&&arrFront[y][x-1]!=arrFront[y][x])||
                (y>0&&x>0&&arrFront[y-1][x]!=arrFront[y][x]&&arrFront[y][x-1]!=arrFront[y][x])){
                    vTiles.push_back(tileManager.getIndicatedSprite((rand()%3)+(((arrFront[y][x]-1)*18)+6)));

                    if(y>0&&x<this->w-1&&arrFront[y-1][x]!=arrFront[y][x]&&arrFront[y][x+1]!=arrFront[y][x]) vTiles[vTiles.size()-1].setAngle(0); ///right-up
                    else if(y<this->h-1&&x<this->w-1&&arrFront[y+1][x]!=arrFront[y][x]&&arrFront[y][x+1]!=arrFront[y][x]) vTiles[vTiles.size()-1].setAngle(90); ///right-down
                    else if(y<this->h-1&&x>0&&arrFront[y+1][x]!=arrFront[y][x]&&arrFront[y][x-1]!=arrFront[y][x]) vTiles[vTiles.size()-1].setAngle(180); ///left-down
                    else if(y>0&&x>0&&arrFront[y-1][x]!=arrFront[y][x]&&arrFront[y][x-1]!=arrFront[y][x]) vTiles[vTiles.size()-1].setAngle(270); ///left-up

                } else if((y>0&&arrFront[y-1][x]!=arrFront[y][x])||(x<this->w-1&&arrFront[y][x+1]!=arrFront[y][x])||
                 (y<this->h-1&&arrFront[y+1][x]!=arrFront[y][x])||(x>0&&arrFront[y][x-1]!=arrFront[y][x])){
                    vTiles.push_back(tileManager.getIndicatedSprite((rand()%3)+(((arrFront[y][x]-1)*18)+3)));

                    if(y>0&&arrFront[y-1][x]!=arrFront[y][x]) vTiles[vTiles.size()-1].setAngle(0); ///up
                    else if(x<this->w-1&&arrFront[y][x+1]!=arrFront[y][x]) vTiles[vTiles.size()-1].setAngle(90); ///right
                    else if(y<this->h-1&&arrFront[y+1][x]!=arrFront[y][x]) vTiles[vTiles.size()-1].setAngle(180); ///down
                    else if(x>0&&arrFront[y][x-1]!=arrFront[y][x]) vTiles[vTiles.size()-1].setAngle(270); ///left
                } else vTiles.push_back(tileManager.getIndicatedSprite((rand()%3)+((arrFront[y][x]-1)*18))); //default
            } else vTiles.push_back(tileManager.getIndicatedSprite(rand()%3));
        }
    }
}

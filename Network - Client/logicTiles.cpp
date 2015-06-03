#include "map.hpp"

#define lTiles (arrFront[y][x]-1)*18

/*Escape here!*/
void rha::cMap::setTiles(unsigned short X, unsigned short Y,
     unsigned short W, unsigned short H){
    if(!vTiles.empty()) vTiles.clear();

    for(int y=0; y<this->size.y; ++y){
        for(int x=0; x<this->size.x; ++x){
            if(arrFront[y][x]>0&&(x<this->size.x-1&&y<this->size.y-1&&y>0&&x>0)){
                //if(arrFront[y-1][x]==arrFront[y][x]&&arrFront[y+1][x]==arrFront[y][x]&&arrFront[y][x+1]==arrFront[y][x]&&arrFront[y][x-1]!=arrFront[y][x])
                  //{vTiles.push_back(tileManager.getIndicatedSprite((rand()%3)+lTiles+17));}

                if(arrFront[y-1][x]==arrFront[y][x]&&arrFront[y][x+1]==arrFront[y][x]&&arrFront[y-1][x+1]!=arrFront[y][x])
                  {vTiles.push_back(tileManager.getIndicatedSprite((rand()%3)+lTiles+9));vTiles[vTiles.size()-1].setAngle(0);}
                else if(arrFront[y+1][x]==arrFront[y][x]&&arrFront[y][x+1]==arrFront[y][x]&&arrFront[y+1][x+1]!=arrFront[y][x])
                  {vTiles.push_back(tileManager.getIndicatedSprite((rand()%3)+lTiles+9)); vTiles[vTiles.size()-1].setAngle(90);}
                else if(arrFront[y+1][x]==arrFront[y][x]&&arrFront[y][x-1]==arrFront[y][x]&&arrFront[y+1][x-1]!=arrFront[y][x])
                  {vTiles.push_back(tileManager.getIndicatedSprite((rand()%3)+lTiles+9)); vTiles[vTiles.size()-1].setAngle(180);}
                else if(arrFront[y-1][x]==arrFront[y][x]&&arrFront[y][x-1]==arrFront[y][x]&&arrFront[y-1][x-1]!=arrFront[y][x])
                  {vTiles.push_back(tileManager.getIndicatedSprite((rand()%3)+lTiles+9)); vTiles[vTiles.size()-1].setAngle(270);}

                else if(arrFront[y-1][x]!=arrFront[y][x]&&arrFront[y][x+1]!=arrFront[y][x]){vTiles.push_back(tileManager.getIndicatedSprite((rand()%3)+lTiles+6)); vTiles[vTiles.size()-1].setAngle(0);} ///right-up
                else if(arrFront[y+1][x]!=arrFront[y][x]&&arrFront[y][x+1]!=arrFront[y][x]){vTiles.push_back(tileManager.getIndicatedSprite((rand()%3)+lTiles+6)); vTiles[vTiles.size()-1].setAngle(90);} ///right-down
                else if(arrFront[y+1][x]!=arrFront[y][x]&&arrFront[y][x-1]!=arrFront[y][x]){vTiles.push_back(tileManager.getIndicatedSprite((rand()%3)+lTiles+6)); vTiles[vTiles.size()-1].setAngle(180);} ///left-down
                else if(arrFront[y-1][x]!=arrFront[y][x]&&arrFront[y][x-1]!=arrFront[y][x]){vTiles.push_back(tileManager.getIndicatedSprite((rand()%3)+lTiles+6)); vTiles[vTiles.size()-1].setAngle(270);} ///left-up

                else if(arrFront[y-1][x]!=arrFront[y][x]){vTiles.push_back(tileManager.getIndicatedSprite((rand()%3)+lTiles+3)); vTiles[vTiles.size()-1].setAngle(0);} ///up
                else if(arrFront[y][x+1]!=arrFront[y][x]){vTiles.push_back(tileManager.getIndicatedSprite((rand()%3)+lTiles+3)); vTiles[vTiles.size()-1].setAngle(90);} ///right
                else if(arrFront[y+1][x]!=arrFront[y][x]){vTiles.push_back(tileManager.getIndicatedSprite((rand()%3)+lTiles+3)); vTiles[vTiles.size()-1].setAngle(180);} ///down
                else if(arrFront[y][x-1]!=arrFront[y][x]){vTiles.push_back(tileManager.getIndicatedSprite((rand()%3)+lTiles+3)); vTiles[vTiles.size()-1].setAngle(270);} ///left

                else vTiles.push_back(tileManager.getIndicatedSprite((rand()%3)+lTiles)); //default
            } else vTiles.push_back(tileManager.getIndicatedSprite(rand()%3)+(2*18));
        }
    }
}

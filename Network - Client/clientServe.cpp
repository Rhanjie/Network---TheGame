#include "client.hpp"

void rha::cClient::managePlayer(sf::Event event){
    switch(event.type){
        case sf::Event::KeyPressed:{
            if(status==PLAYING){
                if((event.key).code==sf::Keyboard::A||(event.key).code==sf::Keyboard::D){
                    if(player.getAction()!=cPlayer::eAction::MOVE){
                        sf::Packet packet;

                        packet<<rha::typePacketsInClient::QUESTION_PLAYER_ACTION<<cPlayer::eAction::MOVE;

                        if((event.key).code==sf::Keyboard::A)
                         packet<<cPlayer::eDirection::LEFT;
                        else packet<<cPlayer::eDirection::RIGHT;
                        if(!manager.sendPacket(&socket, packet)) disconnect();
                    }
                } /*else if((event.key).code==sf::Keyboard::W){
                    player.setAction(cPlayer::eAction::JUMP);
                }*/
            } break;
        }
        case sf::Event::KeyReleased:{
            if(status==PLAYING){
                if((event.key).code==sf::Keyboard::A||(event.key).code==sf::Keyboard::D){
                    sf::Packet packet;

                    if(!manager.sendRawPacket(&socket, rha::typePacketsInClient::QUESTION_PLAYER_STOPACTION)) disconnect();
                }
            } break;
        }
        case sf::Event::MouseWheelMoved:{ //todo - test. (800/600; 4x3)
            float vZoom=0.20f; //todo - option manager

            if((event.mouseWheel).delta<0.0f)
             player.view.zoom(1.0f+vZoom);
            else player.view.zoom(1.0f-vZoom);

            /*float x=player.view.getSize().x+(-(event.mouseWheel).delta*(4*20));
            float y=player.view.getSize().y+(-(event.mouseWheel).delta*(3*20));
            if(x<800&&x>100&&y<600&&y>75)(player.view).setSize(x, y); break;*/
        }
        default: break;
    }
}

void rha::cClient::updateAll(sf::RenderWindow& window){
    if(manager.receivePacket(&socket)){
        switch(manager.getLastTypePacket()){
            case REPLY_OTHERCLIENT_LOGIN:{
                std::string nickHelper;

                if(manager.getLastPacket()>>nickHelper){
                    if(player.nick==nickHelper){std::cout<<"WARNING: Someone logging with your account!\n"; disconnect();}
                    else vOtherPlayers.push_back(cOtherPlayer(nickHelper, (cManagerResources::getObj()).getGraph(1)));
                }
            }
            case INFO_CLIENTS_DATA:{
                sf::Int32 x, y; std::string nick;

                if(manager.getLastPacket()>>nick>>x>>y){
                    if(player.nick==nick){
                        player.regX=x; player.regY=y;
                        player.x=player.regX; player.y=player.regY;
                        //std::cout<<"receive: xy "<<x<<" "<<y<<std::endl;
                        if(!vOtherPlayers.empty()){
                            for(int i=0; i<vOtherPlayers.size(); ++i){
                                if(manager.getLastPacket()>>x>>y){ //todo
                                    vOtherPlayers[i].regX=x; vOtherPlayers[i].regY=y;
                                    vOtherPlayers[i].x=x; vOtherPlayers[i].y=y;
                                    //std::cout<<"receive: other xy ["<<i<<"]: "<<x<<" "<<y<<std::endl;
                                    ((vOtherPlayers[i].textureAnimation).sprite).setPosition(x, y);
                                }
                            }
                        }
                    } break;
                }
            }
            case INFO_PLAYER_ACTION:{
                std::string nick; int converterAction, converterDirection;

                if(manager.getLastPacket()>>nick>>converterAction>>converterDirection){
                    if(player.nick==nick){
                        player.action=static_cast<cPlayer::eAction>(converterAction);
                        player.direction=static_cast<cPlayer::eDirection>(converterDirection);
                        player.textureAnimation.setAnimation(1);
                    }else{
                        for(int i=0; i<vOtherPlayers.size(); ++i){
                            if(vOtherPlayers[i].nick==nick){
                                vOtherPlayers[i].action=static_cast<cOtherPlayer::eAction>(converterAction);
                                vOtherPlayers[i].direction=static_cast<cOtherPlayer::eDirection>(converterDirection);
                                (vOtherPlayers[i].textureAnimation).setAnimation(1); break;
                            }
                        }
                    }
                }
            }
            case INFO_PLAYER_STOPACTION:{
                std::string nick;

                if(manager.getLastPacket()>>nick){
                    if(player.nick==nick){
                        player.action=cPlayer::eAction::STAND;
                        player.textureAnimation.setAnimation(0);
                    }else{for(int i=0; i<vOtherPlayers.size(); ++i){
                            if(vOtherPlayers[i].nick==nick){
                                vOtherPlayers[i].action=cOtherPlayer::eAction::STAND;
                                (vOtherPlayers[i].textureAnimation).setAnimation(0);
                            }
                        }
                    }
                }
            }

            case REPLY_CLIENT_JOIN:{this->join(); break;}
            case ERROR_CLIENT_JOIN:{std::cout<<"No Join!\n"; break;}
        }
    }

    if(!vOtherPlayers.empty()){
     for(int i=0; i<vOtherPlayers.size(); ++i)
      vOtherPlayers[i].performAction();
    }

    player.performAction();
    timer=clock.getElapsedTime();
    if(timer>=sf::seconds(1.0)){ //todo - setting a good value (0.5 is default)
        clock.restart();

        sf::Packet packet;
        packet<<rha::QUESTION_CLIENT_DATA<<player.x<<player.y;
        if(!manager.sendPacket(&socket, packet)) disconnect();
    }
}

void rha::cClient::drawAll(sf::RenderWindow& window){
    window.setView(player.view); mapGame.draw(window);
    for(int i=0; i<vOtherPlayers.size(); ++i){
        if(vOtherPlayers[i].getStatus()==cOtherPlayer::eStatus::PLAYING){
         window.draw((vOtherPlayers[i].textureAnimation).sprite);
            //window.draw(vOtherPlayers[i].text);
        }
    } if(status==PLAYING)window.draw((player.textureAnimation).sprite);
    window.setView(window.getDefaultView());
}

#include "client.hpp"

void rha::cClient::managePlayer(sf::Event event){
    sf::Packet packet;

    switch(event.type){
        case sf::Event::KeyPressed:{
            if(status==PLAYING){
                if((event.key).code==sf::Keyboard::A||(event.key).code==sf::Keyboard::D){
                    if(player.getAction()!=cPlayer::eAction::MOVE){
                        //...

                        packet<<rha::typePacketsInClient::QUESTION_PLAYER_ACTION<<cPlayer::eAction::MOVE;

                        if((event.key).code==sf::Keyboard::A)
                         packet<<cPlayer::eDirection::LEFT;
                        //else
                        if((event.key).code==sf::Keyboard::D)
                        packet<<cPlayer::eDirection::RIGHT;
                        if(!manager.sendPacket(&socket, packet)) disconnect();
                    }
                } /*else if((event.key).code==sf::Keyboard::W){
                    player.setAction(cPlayer::eAction::JUMP);
                }*/
            } break;
        }
        case sf::Event::KeyReleased:{
            if(status==PLAYING&&player.getAction()==cPlayer::eAction::MOVE){
                if((event.key).code==sf::Keyboard::A||(event.key).code==sf::Keyboard::D){
                    //...

                    if(!manager.sendRawPacket(&socket, rha::typePacketsInClient::QUESTION_PLAYER_STOPACTION)) disconnect();
                }
            } break;
        }
        case sf::Event::MouseWheelMoved:{
            float vZoom=0.20f; //todo - option manager

            if((event.mouseWheel).delta<0.0f)
             player.view.zoom(1.0f+vZoom);
            else player.view.zoom(1.0f-vZoom);

            break;
        }
    }
}

void rha::cClient::updateAll(sf::RenderWindow& window){
    sf::Int32 x, y; std::string nick;

    if(manager.receivePacket(&socket)){
        switch(manager.getLastTypePacket()){
            case REPLY_OTHERCLIENT_LOGIN:{
                //...

                if(manager.getLastPacket()>>nick){
                    if(player.nick==nick){std::cout<<"WARNING: Someone logging with your account!\n"; disconnect();} else{
                        //...

                        vOtherPlayers.push_back(cOtherPlayer(nick, (cManagerResources::getObj()).getGraph(1)));
                    }
                } break;
            }


            case REPLY_CLIENT_JOIN:{
                int convTeam, convProfession;

                std::cout<<"Joining the game... ";
                if(manager.getLastPacket()>>x>>y){
                    player.team=static_cast<cPlayer::eTeam>(convTeam);
                    player.profession=static_cast<cPlayer::eProfession>(convProfession);

                    player.spawn(x, y); //todo - test.
                    status=PLAYING; std::cout<<"OK\n";
                } else std::cout<<"ERROR\n"; break;
            }


            case REPLY_OTHERCLIENT_JOIN:{
                int convTeam, convProfession;

                if(manager.getLastPacket()>>nick>>
                 x>>y>>convTeam>>convProfession){
                    for(int i=0; i<vOtherPlayers.size(); ++i){
                        if(vOtherPlayers[i].nick==nick){
                            vOtherPlayers[i].addToGame(x, y, static_cast<cOtherPlayer::eTeam>(convTeam),
                              static_cast<cOtherPlayer::eProfession>(convProfession));
                        }
                    }
                } break;
            }


            case INFO_CLIENTS_DATA:{
                //...

                if(manager.getLastPacket()>>x>>y){
                    player.regX=x; player.regY=y;
                     player.x=x; player.y=y;

                    //std::cout<<"receive: xy "<<x<<" "<<y<<std::endl;
                    for(int i=0; i<vOtherPlayers.size(); ++i){
                        if(manager.getLastPacket()>>x>>y){ //todo
                            vOtherPlayers[i].x=x; vOtherPlayers[i].y=y;
                            vOtherPlayers[i].regX=x; vOtherPlayers[i].regY=y;

                            //std::cout<<"receive: other xy ["<<i<<"]: "<<x<<" "<<y<<std::endl;
                            //((vOtherPlayers[i].textureAnimation).sprite).setPosition(x, y);
                        }
                    }
                } break;
            }


            case INFO_PLAYER_ACTION:{
                int convAction, convDirection;

                if(manager.getLastPacket()>>nick>>convAction>>convDirection){
                    if(player.nick==nick){
                        player.action=static_cast<cPlayer::eAction>(convAction);
                        player.direction=static_cast<cPlayer::eDirection>(convDirection);

                        (player.textureAnimation).setAnimation(1);
                    } else{for(int i=0; i<vOtherPlayers.size(); ++i){
                            if(vOtherPlayers[i].nick==nick){
                                vOtherPlayers[i].action=static_cast<cOtherPlayer::eAction>(convAction);
                                vOtherPlayers[i].direction=static_cast<cOtherPlayer::eDirection>(convDirection);

                                (vOtherPlayers[i].textureAnimation).setAnimation(1); break;
                            }
                        }
                    }
                } break;
            }


            case INFO_PLAYER_STOPACTION:{
                //...

                if(manager.getLastPacket()>>nick){
                    if(player.nick==nick){
                        player.action=cPlayer::eAction::STAND;
                        player.textureAnimation.setAnimation(0);
                    }else{for(int i=0; i<vOtherPlayers.size(); ++i){
                            if(vOtherPlayers[i].nick==nick){
                                vOtherPlayers[i].action=cOtherPlayer::eAction::STAND;
                                (vOtherPlayers[i].textureAnimation).setAnimation(0); break;
                            }
                        }
                    }
                } break;
            }


            case ERROR_CLIENT_JOIN:{std::cout<<"Joining the game... ERROR\n"; break;}
            case NORMAL_SERVER_STOP:{std::cout<<" Server close!\n"; disconnect(); break;}
        }
    }

    for(int i=0; i<vOtherPlayers.size(); ++i)
     vOtherPlayers[i].performAction();
    player.performAction();

    timer=clock.getElapsedTime();
    if(timer>=sf::seconds(1.0)){ //todo - setting a good value (0.5 is default)
        sf::Packet packet;

        clock.restart();
        packet<<rha::QUESTION_CLIENT_DATA<<player.x<<player.y;
        if(!manager.sendPacket(&socket, packet)){std::cout<<" send data failed\n"; disconnect();}
    }
}

void rha::cClient::drawAll(sf::RenderWindow& window){
    //(player.textureAnimation).sprite.rotate(1);

    window.setView(player.view);
    mapGame.draw(window);

    for(int i=0; i<vOtherPlayers.size(); ++i){
        if(vOtherPlayers[i].getStatus()==cOtherPlayer::eStatus::PLAYING){
         window.draw((vOtherPlayers[i].textureAnimation).sprite);
            //window.draw(vOtherPlayers[i].text);
        }
    } if(status==PLAYING) window.draw((player.textureAnimation).sprite);
    window.setView(window.getDefaultView());
}

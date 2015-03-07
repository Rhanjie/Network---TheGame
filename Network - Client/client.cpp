#include "client.hpp"

rha::cClient::cClient(){
    player.nick="anonymous";
    status=eStatus::NOTCONNECT;

    socket.setBlocking(0);
    //vOtherPlayers.push_back(cOtherPlayer("tester", loaderTexture.getGraph(1))); //todo - only test
}

bool rha::cClient::login(std::string nick){
    sf::Packet packet; short timeout=0;
    sf::Clock clock; sf::Time tCheck;

    packet<<rha::typePacketsInClient::QUESTION_CLIENT_LOGIN<<nick;
    if(!manager.sendPacket(&socket, packet))
     return false;
    else player.nick=nick;

    while(1){
        if(timeout>=10){return false; break;}
        tCheck=clock.getElapsedTime();
        if(tCheck>=sf::seconds(1)){
            clock.restart();

            if(manager.receivePacket(&socket)){
                if(manager.getLastTypePacket()==int(rha::typePacketsInServer::REPLY_CLIENT_LOGIN)){
                    std::string nickHelper, nickOtherHelper; sf::Int8 size;

                    if(manager.getLastPacket()>>nickHelper>>size){
                        if(size>0){
                            for(int i=0; i<size; ++i){
                                if(manager.getLastPacket()>>nickOtherHelper)
                                 vOtherPlayers.push_back(cOtherPlayer(nickOtherHelper, loaderTexture.getGraph(1)));
                            }
                        }

                        if(player.nick==nickHelper){return true; break;}
                        else{return false; break;}
                    }else{return false; break;}
                }else if(manager.getLastTypePacket()==int(rha::typePacketsInServer::ERROR_CLIENT_LOGIN)){return false; break;}
            } else timeout+=1;
        }
    }
}

void rha::cClient::connect(sf::IpAddress ip, unsigned short port, std::string nick){
    sf::Clock clock; sf::Time tCheck; short timeout=0;
    server.setData(ip, port);

    while(1){
        if(timeout>=10) break;
        tCheck=clock.getElapsedTime();
        if(tCheck>=sf::seconds(1)){
            clock.restart();
            std::cout<<" Searching connection...\n";
            if(socket.connect(server.getIP(), server.getPort())==sf::Socket::Done){
                std::cout<<"Client is connected!\n";

                if(login(nick)){status=WATCHING; std::cout<<"Client is logged!\n"; break;}
                else{status=NOTCONNECT; std::cout<<"Error - Client isn't logged!\n"; disconnect(); break;}
            } else timeout+=1;
        }
    }
}

bool rha::cClient::join(){
    sf::Int32 x, y; std::string nick;
    int converterTeam, converterProfession;

    if(manager.getLastPacket()>>nick>>x>>y>>converterTeam>>converterProfession){
        std::cout<<player.nick<<" , "<<nick<<std::endl;
        if(player.nick==nick){
            player.team=static_cast<cPlayer::eTeam>(converterTeam);
            player.profession=static_cast<cPlayer::eProfession>(converterProfession);

            player.spawn(x, y);
            std::cout<<"Join!\n";
            status=PLAYING;
        }else{
            if(!vOtherPlayers.empty()){
                for(int i=0; i<vOtherPlayers.size(); ++i){
                    if(vOtherPlayers[i].nick==nick){
                        //vOtherPlayers[i].status==rha::
                        vOtherPlayers[i].x=x; vOtherPlayers[i].y=y;
                        vOtherPlayers[i].team=static_cast<cOtherPlayer::eTeam>(converterTeam);
                        vOtherPlayers[i].profession=static_cast<cOtherPlayer::eProfession>(converterProfession);
                    }
                }
            }
        }
    }
}

/**---***---**/
void rha::cClient::managePlayer(sf::Event event){
    switch(event.type){
        case sf::Event::KeyPressed:{
            if(status==PLAYING){
                if((event.key).code==sf::Keyboard::A||(event.key).code==sf::Keyboard::D){
                    sf::Packet packet;

                    //player.setAction(cPlayer::eAction::MOVE);
                    packet<<rha::typePacketsInClient::QUESTION_PLAYER_ACTION<<cPlayer::eAction::MOVE;

                    /*if((event.key).code==sf::Keyboard::A)
                     player.setDirection(cPlayer::eDirection::LEFT);
                    else player.setDirection(cPlayer::eDirection::RIGHT);*/

                    if((event.key).code==sf::Keyboard::A)
                     packet<<cPlayer::eDirection::LEFT;
                    else packet<<cPlayer::eDirection::RIGHT;

                    if(!manager.sendPacket(&socket, packet)) disconnect(); //todo - test
                    else (player.textureAnimation).setAnimation(2);
                } /*else if((event.key).code==sf::Keyboard::W)
                    player.setAction(cPlayer::eAction::JUMP);*/
            }
            break;
        }
        case sf::Event::KeyReleased:{
            if(status==PLAYING){
                if((event.key).code==sf::Keyboard::A||(event.key).code==sf::Keyboard::D){
                    sf::Packet packet;

                    //player.setAction(cPlayer::eAction::STAND);

                    if(!manager.sendRawPacket(&socket, rha::typePacketsInClient::QUESTION_PLAYER_STOPACTION)) disconnect(); //todo - test
                    else (player.textureAnimation).setAnimation(0);
                }
            }
            break;
        }
        case sf::Event::MouseWheelMoved:{
            float x=player.view.getSize().x+(-(event.mouseWheel).delta*100);
            float y=player.view.getSize().y+(-(event.mouseWheel).delta*100);
            if(x<800&&x>100&&y<600&&y>75)(player.view).setSize(x, y); break;
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
                    if(player.nick==nickHelper){std::cout<<"WARNING: Someone logs in with your account!\n";}
                    else vOtherPlayers.push_back(cOtherPlayer(nickHelper, loaderTexture.getGraph(1)));
                }
            }
            case INFO_CLIENTS_DATA:{ //todo
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
                    }else{
                        for(int i=0; i<vOtherPlayers.size(); ++i){
                            if(vOtherPlayers[i].nick==nick){
                                vOtherPlayers[i].action=static_cast<cOtherPlayer::eAction>(converterAction);
                                vOtherPlayers[i].direction=static_cast<cOtherPlayer::eDirection>(converterDirection);
                                (player.textureAnimation).setAnimation(1);
                            }
                        }
                    }
                }
            }
            case INFO_PLAYER_STOPACTION:{
                std::string nick;

                if(manager.getLastPacket()>>nick){
                    if(player.nick==nick) player.action=cPlayer::eAction::STAND;
                    else{for(int i=0; i<vOtherPlayers.size(); ++i){
                            if(vOtherPlayers[i].nick==nick){
                                vOtherPlayers[i].action=cOtherPlayer::eAction::STAND;
                                (player.textureAnimation).setAnimation(0);
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
        for(int i=0; i<vOtherPlayers.size(); ++i){
            vOtherPlayers[i].performAction();
            ((vOtherPlayers[i].textureAnimation).sprite).setPosition(
                vOtherPlayers[i].x, vOtherPlayers[i].y);
        }
    }

    player.performAction();
    timer=clock.getElapsedTime();
    if(timer>=sf::seconds(0.5)){
        clock.restart();

        sf::Packet packet;
        packet<<rha::QUESTION_CLIENT_DATA<<player.x<<player.y;
        if(!manager.sendPacket(&socket, packet)) disconnect();
    }
}

void rha::cClient::drawAll(sf::RenderWindow& window){
    window.setView(player.view);
    if(status==PLAYING)window.draw((player.textureAnimation).sprite);
    if(!vOtherPlayers.empty()){ //todo - crash
        for(int i=0; i<vOtherPlayers.size(); ++i)
         window.draw((vOtherPlayers[i].textureAnimation).sprite);
    } window.setView(window.getDefaultView());
}

void rha::cClient::disconnect(){
    socket.disconnect();

    status=NOTCONNECT;
}

#include "client.hpp"

rha::cClient::cClient(){
    player.nick="anonymous";
    status=eStatus::NOTCONNECT;

    socket.setBlocking(0);
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
                    std::string nickHelper, nickOtherHelper; sf::Int8 size; int converterStatus;

                    if(manager.getLastPacket()>>nickHelper>>size){
                        if(size>0){
                            for(int i=0; i<size; ++i){
                                if(manager.getLastPacket()>>nickOtherHelper>>converterStatus){
                                 vOtherPlayers.push_back(cOtherPlayer(nickOtherHelper, (cManagerResources::getObj()).getGraph(1)));
                                 vOtherPlayers[i].setStatus(static_cast<cOtherPlayer::eStatus>(converterStatus));
                                }
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
        if(player.nick==nick){
            player.team=static_cast<cPlayer::eTeam>(converterTeam);
            player.profession=static_cast<cPlayer::eProfession>(converterProfession);

            player.spawn(x, y); //todo - test.
            mapGame.setSize(manager.getLastPacket());
            std::cout<<"Join!\n";
            status=PLAYING;
        }else{
            if(!vOtherPlayers.empty()){
                for(int i=0; i<vOtherPlayers.size(); ++i){
                    if(vOtherPlayers[i].nick==nick){
                        vOtherPlayers[i].x=x; vOtherPlayers[i].y=y;
                        vOtherPlayers[i].setStatus(cOtherPlayer::eStatus::PLAYING);
                        vOtherPlayers[i].team=static_cast<cOtherPlayer::eTeam>(converterTeam);
                        vOtherPlayers[i].profession=static_cast<cOtherPlayer::eProfession>(converterProfession);
                    }
                }
            }
        }
    }
}

void rha::cClient::disconnect(){
    socket.disconnect();

    status=NOTCONNECT;
}

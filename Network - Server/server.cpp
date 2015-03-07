#include "server.hpp"

bool rha::cServer::listening(sf::TcpListener* listener, unsigned int port){
    if(listener->listen(port)==sf::Socket::Done){
        setListenerPtr(listener);
        return true;
    } else return false;
}

void rha::cServer::findNewConnection(){
    tgui::ChatBox::Ptr cBoxCopy=gui->get("ChatBox1");

    while(1){
        sf::TcpSocket* newUser=new sf::TcpSocket;
        if(listener->accept(*newUser)!=sf::Socket::Done){delete newUser;}
        else{vClients.push_back(cClient(newUser, "anonymous"));
            cBoxCopy->addLine("New player was connected! - \""+
         (vClients[vClients.size()-1].socket)->getRemoteAddress().toString()+"\"", sf::Color::Blue); //todo - somehow shorten this tapeworm
        }
    }
}

void rha::cServer::serveClients(){
    if(!vClients.empty()){
        for(short i=0; i<vClients.size(); ++i){
            if((vClients[i].player).action==cPlayer::MOVE){
                if((vClients[i].player).direction==cPlayer::LEFT)(vClients[i].player).x+=(vClients[i].player).vX;
                else if((vClients[i].player).direction==cPlayer::RIGHT)(vClients[i].player).x-=(vClients[i].player).vX;
                //...
            }
        }
    }
}

void rha::cServer::receiveData(){
    tgui::ChatBox::Ptr cBoxCopy=gui->get("ChatBox1");
    tgui::ListBox::Ptr lBoxCopy=gui->get("ListBox1");

    while(1){
        if(!vClients.empty()){
            for(short i=0; i<vClients.size(); ++i){
                if(manager.receivePacket(vClients[i].socket)){
                    switch(manager.getLastTypePacket()){
                        case rha::typePacketsInClient::QUESTION_CLIENT_LOGIN:{
                            cBoxCopy->addLine("Receive packet - \"QUESTION_CLIENT_LOGIN\"", sf::Color::White);
                            std::string nick=""; bool protection=false; sf::Packet packet, packetOther; sf::Int8 size;

                            if(manager.getLastPacket()>>nick){
                                if(nick.length()<=0){protection=true; break;}
                                for(short j=0; j<vClients.size(); ++j) //protection
                                 if(vClients[j].nick==nick){protection=true; break;}

                                if(!protection){
                                    lBoxCopy->addItem(nick);
                                    vClients[i].nick=nick;
                                    size=vClients.size()-1;

                                    packet<<rha::typePacketsInServer::REPLY_CLIENT_LOGIN<<vClients[i].nick<<size;
                                    packetOther<<rha::typePacketsInServer::REPLY_OTHERCLIENT_LOGIN<<vClients[i].nick;
                                    if(!vClients.empty()){
                                        for(short j=0; j<vClients.size(); ++j){
                                            if(j!=i){packet<<vClients[j].nick; std::cout<<"ADD NICK IN PACKET\n";}
                                        }
                                    }

                                    if(manager.sendPacket(vClients[i].socket, packet)){
                                        for(short j=0; j<vClients.size(); ++j)
                                         if(j!=i) manager.sendPacket(vClients[j].socket, packetOther);
                                    } cBoxCopy->addLine("New player is connected the game!", sf::Color::Green); break;
                                }else{manager.sendRawPacket(vClients[i].socket, rha::typePacketsInServer::ERROR_CLIENT_LOGIN); vClients.erase(vClients.begin()+i); break;}
                            }else{manager.sendRawPacket(vClients[i].socket, rha::typePacketsInServer::ERROR_CLIENT_LOGIN); vClients.erase(vClients.begin()+i); break;}
                        }
                        case rha::typePacketsInClient::QUESTION_CLIENT_JOIN:{
                            cBoxCopy->addLine("Receive packet - \"QUESTION_CLIENT_JOIN\"", sf::Color::White);
                            bool protection=false; sf::Packet packet;

                            //todo - protection

                            if(!protection){
                                (vClients[i].player).x=20, (vClients[i].player).y=0; //todo - only test
                                (vClients[i].player).team=cPlayer::GREEN;
                                (vClients[i].player).profession=cPlayer::HAMMERDWARF;

                                packet<<rha::typePacketsInServer::REPLY_CLIENT_JOIN<<vClients[i].nick<<(vClients[i].player).x
                                <<(vClients[i].player).y<<int((vClients[i].player).team)<<int((vClients[i].player).profession);

                                if(manager.sendPacket(vClients[i].socket, packet)){
                                    if(!vClients.empty()){
                                        for(short j=0; j<vClients.size(); ++j){
                                            if(j!=i){manager.sendPacket(vClients[j].socket, packet);} //todo - disconnect
                                        }
                                    } vClients[i].status=cClient::PLAYING;
                                    cBoxCopy->addLine("New player is joined the game!", sf::Color::Green);
                                }else{(vClients[i].player).team=cPlayer::NONE; (vClients[i].player).profession=cPlayer::LACK;}
                            }else manager.sendRawPacket(vClients[i].socket, rha::typePacketsInServer::ERROR_CLIENT_JOIN); break;
                        }
                        case rha::typePacketsInClient::QUESTION_CLIENT_DATA:{
                            sf::Int32 x, y; sf::Packet packet;

                            if(manager.getLastPacket()>>x>>y){
                                //... - todo - check position

                                packet<<rha::typePacketsInServer::INFO_CLIENTS_DATA<<vClients[i].nick
                                 <<(vClients[i].player).x<<(vClients[i].player).y;

                                for(short j=0; j<vClients.size(); ++j){
                                    if(vClients[j].getStatus()==cClient::eStatus::PLAYING&&j!=i){
                                     packet<<(vClients[j].player).x<<(vClients[j].player).y;
                                     std::cout<<i<<" - Packet - ["<<j<<"] - "<<(vClients[j].player).x<<std::endl;
                                    }
                                }if(!manager.sendPacket(vClients[i].socket, packet)); //vClients[i].disconnect();
                            } break;
                        }
                        case rha::typePacketsInClient::QUESTION_PLAYER_ACTION:{
                            int converterAction, converterDirection; sf::Packet packet;

                            if(manager.getLastPacket()>>converterAction>>converterDirection){
                                (vClients[i].player).action=static_cast<cPlayer::eAction>(converterAction);
                                (vClients[i].player).direction=static_cast<cPlayer::eDirection>(converterDirection);

                                packet<<rha::typePacketsInServer::INFO_PLAYER_ACTION<<vClients[i].nick
                                 <<int((vClients[i].player).action)<<int((vClients[i].player).direction);
                                manager.sendPacket(vClients[i].socket, packet);

                                for(short j=0; j<vClients.size(); ++j)
                                 if(j!=i) manager.sendPacket(vClients[j].socket, packet);
                            } break;
                        }
                        case rha::typePacketsInClient::QUESTION_PLAYER_STOPACTION:{
                            sf::Packet packet;

                            (vClients[i].player).action=cPlayer::STAND;
                            packet<<rha::typePacketsInServer::INFO_PLAYER_STOPACTION<<vClients[i].nick;
                             //<<int((vClients[i].player).action)<<int((vClients[i].player).direction);
                            manager.sendPacket(vClients[i].socket, packet);

                            for(short j=0; j<vClients.size(); ++j)
                             if(j!=i) manager.sendPacket(vClients[j].socket, packet);
                            break;
                        }
                    }
                }
            }
        }
    }
}

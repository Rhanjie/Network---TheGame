#include "server.hpp"

#define ipAddress (vClients[vClients.size()-1].socket)->getRemoteAddress().toString()
#define deleteClient vClients.erase(vClients.begin()+i)

bool rha::cServer::listening(sf::TcpListener* listener, unsigned int port){
    tMap.setSize(sf::Vector2u(15,15));

    if(listener->listen(port)==sf::Socket::Done){
        setListenerPtr(listener); return true;
    } else return false;
}

void rha::cServer::findNewConnection(tgui::Gui* gui, bool* run, bool* stop){
    tgui::ChatBox::Ptr cBoxCopy=gui->get("ChatBox1");

    while(*run){
        sf::TcpSocket* newUser=new sf::TcpSocket;
        if(listener->accept(*newUser)==sf::Socket::Done){
            vClients.push_back(cClient(newUser, "anonymous"));

            cBoxCopy->addLine("New user connect! ["+ipAddress+"]", sf::Color::Green);
        } else delete newUser; //delete this thread if run=false
    } *stop=true;
}

void rha::cServer::serveClients(){
    for(short i=0; i<vClients.size(); ++i){
        if((vClients[i].player).action==cPlayer::MOVE){
            if((vClients[i].player).direction==cPlayer::LEFT)(vClients[i].player).x-=(vClients[i].player).vX;
            else if((vClients[i].player).direction==cPlayer::RIGHT)(vClients[i].player).x+=(vClients[i].player).vX;

            //...
        }
    }
}

void rha::cServer::receiveData(tgui::Gui* gui, bool* run, bool* stop){
    sf::Packet packet; int action, direction;
    bool protection=false; sf::Int32 x, y; //position in 32bit.

    tgui::ChatBox::Ptr cBoxCopy=gui->get("ChatBox1");
    tgui::ListBox::Ptr lBoxCopy=gui->get("ListBox1");

    while(*run){ //todo - optimization.
        for(short i=0; i<vClients.size(); ++i){
            if(manager.receivePacket(vClients[i].socket)){
                switch(manager.getLastTypePacket()){
                    case rha::typePacketsInClient::QUESTION_CLIENT_LOGIN:{
                        cBoxCopy->addLine("Receive packet (LOGIN) from ["+vClients[i].nick+"]", sf::Color::White);
                        std::string nick=""; sf::Packet packetOther; int size=vClients.size()-1;

                        if(manager.getLastPacket()>>nick){
                            for(short j=0; j<vClients.size(); ++j){if(j!=i&&vClients[j].nick==nick) protection=true;}
                             if(vClients[i].nick==nick||nick.length()<=0||nick.length()>15){protection=true;}

                            if(!protection){
                                lBoxCopy->addItem(nick); vClients[i].nick=nick;

                                packet<<rha::typePacketsInServer::REPLY_CLIENT_LOGIN<<size;
                                packetOther<<rha::typePacketsInServer::REPLY_OTHERCLIENT_LOGIN<<vClients[i].nick;
                                for(short j=0; j<vClients.size(); ++j){if(j!=i){packet<<vClients[j].nick<<int(vClients[j].getStatus());}}

                                packet<<tMap.getSize().x<<tMap.getSize().y;
                                for(int y=0; y<tMap.getSize().y; ++y){
                                    for(int x=0; x<tMap.getSize().x; ++x){
                                        packet<<tMap.arrFront[y][x]<<tMap.arrBack[y][x];
                                    }
                                }

                                if(manager.sendPacket(vClients[i].socket, &packet)){
                                    this->sendAll(i, &packetOther);
                                } vClients[i].setStatus(cClient::eStatus::WATCHING);

                                cBoxCopy->addLine(vClients[i].nick+" joined the spectators!", sf::Color::Yellow);
                            } else{manager.sendRawPacket(vClients[i].socket, rha::typePacketsInServer::ERROR_CLIENT_LOGIN); deleteClient;}
                        } else{manager.sendRawPacket(vClients[i].socket, rha::typePacketsInServer::ERROR_CLIENT_LOGIN); deleteClient;}
                            packet.clear(); protection=false; break;
                    }


                    case rha::typePacketsInClient::QUESTION_CLIENT_JOIN:{
                        cBoxCopy->addLine("Receive packet (JOIN) from ["+vClients[i].nick+"]", sf::Color::White);
                        sf::Packet packetOther;

                        if(vClients[i].getStatus()==cClient::eStatus::PLAYING) protection=true;

                        if(!protection){ //todo - add method for spawn player
                            (vClients[i].player).x=20, (vClients[i].player).y=0;
                            (vClients[i].player).team=cPlayer::GREEN;
                            (vClients[i].player).profession=cPlayer::HAMMERDWARF;

                            packet<<rha::typePacketsInServer::REPLY_CLIENT_JOIN<<int((vClients[i].player).x)<<int((vClients[i].player).y);
                            packetOther<<rha::typePacketsInServer::REPLY_OTHERCLIENT_JOIN<<vClients[i].nick<<int((vClients[i].player).x)
                             <<int((vClients[i].player).y)<<int((vClients[i].player).team)<<int((vClients[i].player).profession);

                            if(manager.sendPacket(vClients[i].socket, &packet)){
                                 this->sendAll(i, &packetOther);
                                vClients[i].setStatus(cClient::PLAYING);

                                cBoxCopy->addLine(vClients[i].nick+" joined the game!", sf::Color::Yellow);
                            } else{(vClients[i].player).team=cPlayer::NONE; (vClients[i].player).profession=cPlayer::LACK;}
                        } else manager.sendRawPacket(vClients[i].socket, rha::typePacketsInServer::ERROR_CLIENT_JOIN);
                            packet.clear(); protection=false; break;
                    }


                    case rha::typePacketsInClient::QUESTION_CLIENT_DATA:{
                        ///cBoxCopy->addLine("Receive packet (DATA) from ["+vClients[i].nick+"]", sf::Color::White);
                        //...

                        if(manager.getLastPacket()>>x>>y){
                            //... - todo - check position

                            packet<<rha::typePacketsInServer::INFO_CLIENTS_DATA
                             <<(vClients[i].player).x<<(vClients[i].player).y;

                            for(short j=0; j<vClients.size(); ++j){
                                if(vClients[j].getStatus()==cClient::eStatus::PLAYING&&j!=i){
                                    packet<<(vClients[j].player).x<<(vClients[j].player).y;
                                   std::cout<<i<<" - Packet - ["<<j<<"] - "<<(vClients[j].player).x<<std::endl;
                                }
                            } if(!manager.sendPacket(vClients[i].socket, &packet)){
                                //{vClients.erase(vClients[i]) //vClients[i].disconnect();
                            }
                        } else{/*packet destroyed.*/}
                            packet.clear(); break;
                    }


                    case rha::typePacketsInClient::QUESTION_PLAYER_ACTION:{
                        ///cBoxCopy->addLine("Receive packet (MOVE) from ["+vClients[i].nick+"]", sf::Color::White);
                        //...

                        if(manager.getLastPacket()>>action>>direction){
                            (vClients[i].player).action=static_cast<rha::cPlayer::eAction>(action);
                            (vClients[i].player).direction=static_cast<rha::cPlayer::eDirection>(direction);

                            packet<<rha::typePacketsInServer::INFO_PLAYER_ACTION<<vClients[i].nick
                             <<int((vClients[i].player).action)<<int((vClients[i].player).direction);
                            if(manager.sendPacket(vClients[i].socket, &packet)){
                                this->sendAll(i, &packet);
                            } //todo - optimization.
                        } else{/*packet destroyed.*/}
                            packet.clear(); break;
                    }


                    case rha::typePacketsInClient::QUESTION_PLAYER_STOPACTION:{
                        ///cBoxCopy->addLine("Receive packet (STOP) from ["+vClients[i].nick+"]", sf::Color::White);
                        //...

                        (vClients[i].player).action=cPlayer::STAND;
                        packet<<rha::typePacketsInServer::INFO_PLAYER_STOPACTION<<vClients[i].nick;
                        if(manager.sendPacket(vClients[i].socket, &packet)){
                            this->sendAll(i, &packet);
                        } else{/*...*/}
                        packet.clear(); break;
                    }

                    case rha::typePacketsInClient::NORMAL_CLIENT_STOP:{
                        std::cout<<"Disconnect "<<vClients[i].nick<<"\n";

                        packet<<rha::typePacketsInServer::REPLY_OTHERCLIENT_STOP<<vClients[i].nick;
                        this->sendAll(i, &packet);

                        vClients.erase(vClients.begin()+i);
                         packet.clear(); break;
                    }
                }
            }
        }
    } *stop=true;
}


void rha::cServer::releaseResources(){
    for(short j=0; j<vClients.size(); ++j)
     manager.sendRawPacket(vClients[j].socket, rha::typePacketsInServer::NORMAL_SERVER_STOP);

    vClients.clear(); listener=nullptr;
    tMap.setSize(sf::Vector2u(0, 0));
}

void rha::cServer::sendAll(short &which, sf::Packet* packet){
    for(short i=0; i<vClients.size(); ++i)
     if(i!=which) if(manager.sendPacket(vClients[i].socket, packet)){/*...*/};
}

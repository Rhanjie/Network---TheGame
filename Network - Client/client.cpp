#include "client.hpp"

rha::cClient::cClient(){
    player.nick="anonymous";
    status=eStatus::NOTCONNECT;

    socket.setBlocking(1);
}

void rha::cClient::connect(sf::IpAddress ip, unsigned short port, std::string nick){
    socket.setBlocking(true);

    server.setData(ip, port);
    std::cout<<"Searching connection... ";
    if(socket.connect(server.getIP(), server.getPort())==sf::Socket::Done){
        std::cout<<"OK\nLogging... ";

        std::this_thread::sleep_for(std::chrono::seconds(1));
        if(login(nick)){status=WATCHING; std::cout<<"OK\n";}
        else{status=NOTCONNECT; std::cout<<"ERROR\n"; disconnect();}
    } else std::cout<<"ERROR\n";
    socket.setBlocking(false);
}

bool rha::cClient::login(std::string nick){
    sf::Packet packet;

    packet<<rha::typePacketsInClient::QUESTION_CLIENT_LOGIN<<nick;
    if(!manager.sendPacket(&socket, &packet)) return false;
     else player.nick=nick;

    if(manager.receivePacket(&socket)){
        if(manager.getLastTypePacket()==int(rha::typePacketsInServer::REPLY_CLIENT_LOGIN)){
            std::string nickHelper; int size=0; int converterStatus;

            if(manager.getLastPacket()>>size){
                 for(int i=0; i<size; ++i){
                    if(manager.getLastPacket()>>nickHelper>>converterStatus){
                        vOtherPlayers.push_back(cOtherPlayer(nickHelper, (cManagerResources::getObj()).getGraph(1)));
                        vOtherPlayers[i].setStatus(static_cast<cOtherPlayer::eStatus>(converterStatus));
                    }
                }

                mapGame.setSize(manager.getLastPacket());
            } else{std::cout<<"Corrupted packet!\n"; return false;}
        } else{if(manager.getLastTypePacket()==rha::typePacketsInServer::ERROR_CLIENT_LOGIN) return false;}
    } return true;
}

void rha::cClient::disconnect(){
    manager.sendRawPacket(&socket, rha::typePacketsInClient::NORMAL_CLIENT_STOP);

     socket.disconnect();
     status=NOTCONNECT;
    std::cout<<"Disconnect!\n";
}

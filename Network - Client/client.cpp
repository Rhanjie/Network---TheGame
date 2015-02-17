#include "client.hpp"

rha::cClient::cClient(){
    nick="anonymous";
    isConnect=false;

    socket.setBlocking(0);
}

bool rha::cClient::login(std::string nick){
    sf::Packet packet; short timeout=0;
    sf::Clock clock; sf::Time tCheck;

    packet<<rha::typePacketsInClient::QUESTION_CLIENT_LOGIN<<nick;
    if(!manager.sendPacket(&socket, packet))
     return false;

    while(1){
        if(timeout>=10){return false; break;}
        tCheck=clock.getElapsedTime();
        if(tCheck>=sf::seconds(1)){
            clock.restart();

            if(manager.receivePacket(&socket)){
                if(manager.getLastTypePacket()==int(rha::typePacketsInServer::REPLY_CLIENT_LOGIN)){return true; break;}
                 else if(manager.getLastTypePacket()==int(rha::typePacketsInServer::ERROR_CLIENT_LOGIN)){return false; break;}
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
            std::cout<<"Searching for connection...\n";
            if(socket.connect(server.getIP(), server.getPort())==sf::Socket::Done){
                std::cout<<"Client is connected!\n";

                this->nick=nick;
                if(login(nick)){isConnect=true; std::cout<<"Client is logged!\n"; break;}
                else{isConnect=false; std::cout<<"Error - Client isn't logged!\n"; disconnect(); break;}
            } else timeout+=1;
        }
    }
}

void rha::cClient::disconnect(){
    socket.disconnect();

    isConnect=false;
}

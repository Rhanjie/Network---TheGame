#include "client.hpp"

rha::cClient::cClient(cServerInfo* server){
    this->server=server;

    player=NULL;
    nick="anonymous";
    password="pass";

    isConnect=false;
}

void rha::cClient::connect(sf::IpAddress ip, unsigned short port){
    sf::Clock clock; sf::Time tCheck; short timeout=0;
    server->setData(ip, port);

    while(1){
        if(timeout>=10) break;
        tCheck=clock.getElapsedTime();
        if(tCheck>=sf::seconds(1)){
            clock.restart();
            std::cout<<"Searching for connection...\n";
            if((server->socket).connect(server->getIP(), server->getPort())==sf::Socket::Done){
                isConnect=true;

                std::cout<<" Connect!\n"; break;
            } else{std::cout<<" No connect!\n"; timeout+=1;}
        }
    }
}

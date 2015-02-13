#include "client.hpp"

rha::cClient::cClient(){
    nick="anonymous";
    isConnect=false;

    socket.setBlocking(0);
}

void rha::cClient::connect(sf::IpAddress ip, unsigned short port){
    sf::Clock clock; sf::Time tCheck; short timeout=0;
    server.setData(ip, port);

    while(1){
        if(timeout>=10) break;
        tCheck=clock.getElapsedTime();
        if(tCheck>=sf::seconds(1)){
            clock.restart();
            std::cout<<"Searching for connection...\n";
            if(socket.connect(server.getIP(), server.getPort())==sf::Socket::Done){
                isConnect=true;

                manager.sendRawPacket(&socket, "test"); //test

                std::cout<<" Connect!\n"; break;
            } else{std::cout<<" No connect!\n"; timeout+=1;}
        }
    }
}

void rha::cClient::disconnect(){
    socket.disconnect();

    isConnect=false;
}

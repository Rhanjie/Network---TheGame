#include "server.hpp"

bool rha::cServer::listening(sf::TcpListener* listener, unsigned int port){
    if(listener->listen(port)==sf::Socket::Done){
        selector.add(*listener);
        return true;
    } else return false;
}

bool rha::cServer::findNewConnection(sf::TcpListener* listener){
    if(selector.isReady(*listener)){
        sf::TcpSocket* newUser=new sf::TcpSocket;
        listener->accept(*newUser);
        vClients.push_back(cClient(newUser, "nick"));
        selector.add(*newUser);

        return true;
    } else return false;
}

void rha::cServer::serveClients(){
    if(!vClients.empty()){
        for(short i=0; i<vClients.size(); ++i){
            if(selector.isReady(*vClients[i].socket)){
                if(manager.receivePacket(vClients[i].socket)){
                    if(manager.getLastTypePacket()=="test"){ //todo - only test
                        std::cout<<"Receive packet - test!\n";
                    }
                }
            }
        }
    }
}

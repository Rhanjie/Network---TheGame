#include "server.hpp"

bool rha::cServer::listening(sf::TcpListener* listener, unsigned int port){
    if(listener->listen(port)==sf::Socket::Done){
        selector.add(*listener);
        return true;
    } else return false;
}

bool rha::cServer::findNewConnection(sf::TcpListener* listener, tgui::Gui& gui){
    tgui::ChatBox::Ptr cBoxCopy=gui.get("ChatBox1");

    if(selector.isReady(*listener)){
        sf::TcpSocket* newUser=new sf::TcpSocket;
        listener->accept(*newUser);
        vClients.push_back(cClient(newUser, "anonymous"));
        selector.add(*newUser);

        cBoxCopy->addLine("New player was connected! - \""+
         (vClients[vClients.size()-1].socket)->getRemoteAddress().toString()+"\"", sf::Color::Black); //todo - somehow shorten this tapeworm
        return true;
    } else return false;
}

void rha::cServer::serveClients(tgui::Gui& gui){
    tgui::ChatBox::Ptr cBoxCopy=gui.get("ChatBox1");
    tgui::ListBox::Ptr lBoxCopy=gui.get("ListBox1");

    if(!vClients.empty()){
        for(short i=0; i<vClients.size(); ++i){
            if(selector.isReady(*vClients[i].socket)){
                if(manager.receivePacket(vClients[i].socket)){
                    switch(manager.getLastTypePacket()){
                        case rha::typePacketsInClient::QUESTION_CLIENT_LOGIN:{
                            cBoxCopy->addLine("Receive packet - \"QUESTION_CLIENT_LOGIN\"", sf::Color::Black);
                            std::string nick=""; bool protection=false;

                            if(manager.getLastPacket()>>nick){
                                for(short j=0; j<vClients.size(); ++j)
                                 if(vClients[j].nick==nick){protection=true; break;}

                                if(!protection){
                                    lBoxCopy->addItem(nick);
                                    vClients[i].nick=nick;
                                    manager.sendRawPacket(vClients[i].socket, rha::typePacketsInServer::REPLY_CLIENT_LOGIN);
                                    cBoxCopy->addLine("Send packet - \"REPLY_CLIENT_LOGIN\"", sf::Color::Green); break;
                                } else manager.sendRawPacket(vClients[i].socket, rha::typePacketsInServer::ERROR_CLIENT_LOGIN); vClients.erase(vClients.begin()+i); break;
                            } else manager.sendRawPacket(vClients[i].socket, rha::typePacketsInServer::ERROR_CLIENT_LOGIN); vClients.erase(vClients.begin()+i); break;
                        }
                        //case rha::typePacketsInServer::TEST:
                            //break;
                    }
                }
            }
        }
    }
}

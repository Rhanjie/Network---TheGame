#include "clients.hpp"

rha::cClient::cClient(sf::TcpSocket* socket, std::string nick){
    this->socket=socket;
    this->nick=nick;

    status=WATCHING;
    socket->setBlocking(0);
}

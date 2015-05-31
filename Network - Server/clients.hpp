#ifndef CLIENTS_HPP_INCLUDED
#define CLIENTS_HPP_INCLUDED
#include "managerLibs.hpp"
#include "players.hpp"

namespace rha{
    class cClient{
        public:
         enum eStatus{WATCHING, PLAYING};
        private:
         eStatus status;
        public:
         cPlayer player;
         sf::TcpSocket* socket;
         std::string nick;

         cClient(sf::TcpSocket* socket, std::string nick);

         void setStatus(eStatus status){this->status=status;}
         inline eStatus getStatus(){return status;}
    };
}

#endif // CLIENTS_HPP_INCLUDED

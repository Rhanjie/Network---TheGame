#ifndef CLIENTS_HPP_INCLUDED
#define CLIENTS_HPP_INCLUDED
#include "managerLibs.hpp"
#include "players.hpp"

namespace rha{
    class cClient{
        public:
         enum eStatus{WATCHING, PLAYING};
        private:
         //cPlayer player;
         //sf::TcpSocket* socket;

         //std::string nick;
         //eStatus status;
        public:
         cPlayer player; //todo
         sf::TcpSocket* socket;
         std::string nick;
         eStatus status;

         cClient(sf::TcpSocket* socket, std::string nick);
         //void

         inline bool getStatus(){return &status;}
    };
}

#endif // CLIENTS_HPP_INCLUDED

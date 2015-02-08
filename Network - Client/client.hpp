#ifndef CLIENT_HPP_INCLUDED
#define CLIENT_HPP_INCLUDED
#include "managerLibs.hpp"
#include "player.hpp"

namespace rha{
    class cClient{
        private:
         cPlayer* player;
         std::string nick;
         std::string password;

         bool isConnect;
        public:
         cClient();
         void connect();

         //registration&login todo..
         inline bool getConnect(){return isConnect;}
    };
}

#endif // CLIENT_HPP_INCLUDED

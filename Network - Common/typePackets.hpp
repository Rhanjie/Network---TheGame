#ifndef TYPEPACKETS_HPP_INCLUDED
#define TYPEPACKETS_HPP_INCLUDED
#include "managerLibs.hpp"

namespace rha{
    enum typePacketsInServer{ //receive in client, send in server
        NORMAL_SERVER_NULL,
        REPLY_CLIENT_LOGIN,
         REPLY_OTHERCLIENT_LOGIN,
         ERROR_CLIENT_LOGIN,
        REPLY_CLIENT_JOIN,
         ERROR_CLIENT_JOIN,

        INFO_CLIENT_NEW,
         INFO_CLIENTS_DATA,
        INFO_CLIENT_POSITION,

        INFO_PLAYER_ACTION,
        INFO_PLAYER_STOPACTION,
        //...
    };
    enum typePacketsInClient{ //receive in server, send in client
        NORMAL_CLIENT_NULL,
        QUESTION_CLIENT_LOGIN,
        QUESTION_CLIENT_JOIN,

        QUESTION_PLAYER_ACTION,
        QUESTION_PLAYER_STOPACTION,
        QUESTION_CLIENT_DATA,
        //...
    };
}

#endif // TYPEPACKETS_HPP_INCLUDED

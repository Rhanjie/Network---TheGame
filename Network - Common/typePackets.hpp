#ifndef TYPEPACKETS_HPP_INCLUDED
#define TYPEPACKETS_HPP_INCLUDED
#include "managerLibs.hpp"

namespace rha{
    /*Receive in client, send in server*/
    enum typePacketsInServer{
        NORMAL_SERVER_NULL,
        NORMAL_SERVER_STOP,

        REPLY_CLIENT_LOGIN,
        REPLY_CLIENT_JOIN,
        ERROR_CLIENT_LOGIN,
        ERROR_CLIENT_JOIN,

        REPLY_OTHERCLIENT_LOGIN,
        REPLY_OTHERCLIENT_JOIN,

        INFO_CLIENT_NEW,
        INFO_CLIENT_POSITION,
        INFO_CLIENTS_DATA,

        INFO_PLAYER_ACTION,
        INFO_PLAYER_STOPACTION,
    };

    /*Receive in server, send in client*/
    enum typePacketsInClient{
        NORMAL_CLIENT_NULL,
        NORMAL_CLIENT_STOP,

        QUESTION_CLIENT_LOGIN,
        QUESTION_CLIENT_JOIN,
        QUESTION_CLIENT_DATA,

        QUESTION_PLAYER_ACTION,
        QUESTION_PLAYER_STOPACTION,
    };
}

#endif // TYPEPACKETS_HPP_INCLUDED

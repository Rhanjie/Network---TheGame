#ifndef TYPEPACKETS_HPP_INCLUDED
#define TYPEPACKETS_HPP_INCLUDED
#include "managerLibs.hpp"

namespace rha{
    enum typePacketsInServer{ //receive in client, send in server
        NORMAL_SERVER_NULL,
        REPLY_CLIENT_LOGIN,
         ERROR_CLIENT_LOGIN,
        //...
    };
    enum typePacketsInClient{ //receive in server, send in client
        NORMAL_CLIENT_NULL,
        QUESTION_CLIENT_LOGIN,
        //...
    };
}

#endif // TYPEPACKETS_HPP_INCLUDED

//
// Created by Tristan Ratz on 11.04.18.
//

#ifndef PANCAKESOCKET_SERVER_H
#define PANCAKESOCKET_SERVER_H

#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <iostream>
#include <string>

#include "Client.h"

using namespace std;


class Server
{
    public:
        Server(int port);
        int getPort() const;

        int acceptNewClient();

    protected:
        int s;
        int port;
        int portno;
        struct sockaddr_in server;

        int createClientQueue(int waitingClients);
};


#endif //PANCAKESOCKET_SERVER_H

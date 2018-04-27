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
        /**
         * Server
         *
         * Initializes and opens new server
         *
         * @param port PortNr of the Server
         */
        Server(int port);

        /**
         * getPort
         *
         * @return port number of the server
         */
        int getPort() const;

        /**
         * acceptNewClient
         *
         * Blocking method which accepts a new client from the clientqueue.
         *
         * @return socket ID of a new connection point with a client
         */
        int acceptNewClient();

    protected:
        int sockID;                 // Socket
        int port;                   // port
        struct sockaddr_in server;  // Server configuration

        /**
         * createClientQueue
         *
         * Creates an queue with the amount of clients that
         * can be waiting in the queue until they get declined
         * - is called in the server constructor
         *
         * @param waitingClients The amount of clients
         * @return -1 on error else should be == waitingClients
         */
        int createClientQueue(int waitingClients);
};


#endif //PANCAKESOCKET_SERVER_H

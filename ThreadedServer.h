//
// Created by Tristan Ratz on 23.04.18.
//

#ifndef PANCAKESOCKET_THREADEDSERVER_H
#define PANCAKESOCKET_THREADEDSERVER_H

#include <thread>
#include <stdlib.h>

#include "Server.h"
#include "LinkedList/LinkedList.h"
#include "config.h"

class ThreadedServer : Server
{
        typedef LinkedList<Client *> ClientList;

    protected:
        thread *serverThreads[2];
        ClientList *cl;

        void * startAcceptLoop();
        void * startRecievingLoop();
        void recievedData(Client *c);

    public:
        ThreadedServer(int port);
};


#endif //PANCAKESOCKET_THREADEDSERVER_H

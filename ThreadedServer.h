//
// Created by Tristan Ratz on 23.04.18.
//

#ifndef PANCAKESOCKET_THREADEDSERVER_H
#define PANCAKESOCKET_THREADEDSERVER_H

#include <thread>
#include <stdlib.h>
#include <list>

#include "Server.h"
#include "LinkedList/LinkedList.h"
#include "config.h"

class ThreadedServer : Server
{
        typedef LinkedList<Client *> ClientList;

    protected:
        thread serverThreads[2];
        LinkedList<Client> cl;

        void * startAcceptLoop();
        void * startRecievingLoop();
        void recievedData(Client &c);

    public:
        ThreadedServer(int port);

        void recievedData(Client *c);
};


#endif //PANCAKESOCKET_THREADEDSERVER_H

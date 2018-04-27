/**
 * ThreadedServer
 *
 * A multi-threaded, multi-client server
 * To use it just let your object inherit from it
 * Or use the built in lambda functionality.
 * Created by Pancake Software, Tristan Ratz on 23.04.18.
 */

#ifndef PANCAKESOCKET_THREADEDSERVER_H
#define PANCAKESOCKET_THREADEDSERVER_H

#include <thread>
#include <stdlib.h>
#include <list>
#include <iostream>

#include "Server.h"
#include "LinkedList/LinkedList.h"
#include "config.h"

class ThreadedServer : Server
{
    protected:
        std::thread mainThread;
        LinkedList<Client> cl;

        void startAcceptLoop();
        void mainThreadLoop();
        void receivedData(Client &c);

        std::function<void(Client *)> function;

        Log l;

    public:
        ThreadedServer(int port);
        ThreadedServer(int port,  std::function<void(Client *)> f);
        ~ThreadedServer();

        void receivingThreadLoop(Client *c);

    void removeClient(Client *cl);
};


#endif //PANCAKESOCKET_THREADEDSERVER_H

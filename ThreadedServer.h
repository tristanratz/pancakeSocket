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
    public:
        /**
         * ThreadedServer
         *
         * Initializes and opens new multi threaded server
         *
         * @param port portNr of the server
         */
        ThreadedServer(int port);

        /**
         * ThreadedServer
         *
         * Initializes and opens new multi threaded server
         *
         * @param port portNr of the server
         * @param f the function which will be called all the time to receive data
         */
        ThreadedServer(int port,  std::function<void(Client &)> f);

        void receivingThreadLoop(Client &c);

        /**
         * removeClient
         *
         * removes (from cl) and  deinitializes client
         *
         * @param cl client to be removed
         */
        void removeClient(Client &c);

    protected:
        std::thread mainThread;     // the main thread for accepting new clients
        LinkedList<Client> cl;      // the client list with all clients
        Log l;                      // a logging object

        // Events
        std::function<void(Client&)> receiveHandler; // the function which gets called in a own thread all the time to receive data
        std::function<void(Client&, LinkedList<Client>&)> onConnection;
        std::function<void(Client&, LinkedList<Client>&)> onDisconnection;

        /**
         * mainThreadLoop
         *
         * the main thread loop where new clients get accepted
         */
        void mainThreadLoop();

        void setDisconnectionEvent(function<void(Client &, LinkedList<Client> &)> f);

        void setConnectionEvent(function<void(Client &, LinkedList<Client> &)> f);
};


#endif //PANCAKESOCKET_THREADEDSERVER_H

/**
 * ThreadedServer
 *
 * A multi-threaded, multi-client server
 * To use it just let your object inherit from it
 * Or use the built in lambda functionality.
 * Created by Pancake Software, Tristan Ratz on 23.04.18.
 */

#include "ThreadedServer.h"
#include "Log/Log.h"

ThreadedServer::ThreadedServer(int port) : Server(port), cl() {
    l = Log("Threaded Server");
    l.info("Initializing Server...");
    try
    {
        function  = [] (Client * c) -> void {};
        serverThreads[0] = std::thread(&ThreadedServer::startAcceptLoop, this);
        serverThreads[0].detach();
        l.info("Initialized first Thread");
        serverThreads[1] = std::thread(&ThreadedServer::startReceivingLoop, this);
        serverThreads[1].detach();
    } catch (const std::exception& e) {
        perror("ERROR");
        cout << e.what();
        exit(-1);
    }
    l.info("Initialized both Threads");
}

ThreadedServer::ThreadedServer(int port, void (*func)(Client *)) : ThreadedServer(port)
{
    function = func;
}

ThreadedServer::~ThreadedServer()
{
    //delete(function);
}


void ThreadedServer::startReceivingLoop() {
    try
    {
        l.ok("Started first thread");
        while (true)
        {
            for (int i = 0; i < cl.size(); i++)
            {
                this->receivedData(cl.get(i));
                l.info("Data recieved");

                if (cl.get(i)->isConnected()) {
                    delete cl.get(i);
                }
            }

            //l.ok("1: Go to sleep");
            sleep(THREAD_WAIT);
        }
        return;
    } catch (const std::exception& e) {
        perror("ERROR");
        cout << e.what();
        exit(-1);
    }
}

void ThreadedServer::startAcceptLoop() {
    try
    {
        l.ok("Started second Thread");

        while (true)
        {
            int i = this->acceptNewClient();
            if (i >= 0)
            {
                l.info("Client ID: " + to_string(i));
                Client c = Client(i, server, this);
                l.info("Client connected");
                cl.add(c);
            } else {
            }

            //l.ok("2: Go to sleep");
            sleep(THREAD_WAIT);
        }
        return;
    } catch (const std::exception& e) {
        perror("ERROR");
        cout << e.what();
        exit(-1);
    }
}


void ThreadedServer::receivedData(Client *c) {
    // Here you have to write content
    function(c);
    l.info("Client Message: " + string(c->recieve()));
}

void ThreadedServer::removeClient(Client *c) {
    this->cl.remove(cl.getID(*c));
}

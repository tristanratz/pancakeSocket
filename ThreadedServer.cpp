//
// Created by Tristan Ratz on 23.04.18.
//

#include "ThreadedServer.h"

ThreadedServer::ThreadedServer(int port) : Server(port), cl() {
    serverThreads[0] = thread(&ThreadedServer::startAcceptLoop, this);
    serverThreads[1] = thread(&ThreadedServer::startRecievingLoop, this);
}

void * ThreadedServer::startRecievingLoop() {
    while (true)
    {
        for (int i = 0; i < cl.size(); i++)
        {
            if (cl.get(i)->recievedData())
            {
                this->recievedData(cl.get(i));
            }
        }

        // Hier auf empfangene Dateien und auf geschlossene Sockets schauen (deinitialisieren und
        sleep(THREAD_WAIT);
    }
}

void * ThreadedServer::startAcceptLoop() {
    while (true)
    {
        Client c = Client(this->acceptNewClient(), server);

        cl.add(c);

        sleep(THREAD_WAIT);
    }

}


void ThreadedServer::recievedData(Client *c) {
    // Here you have to write content

}
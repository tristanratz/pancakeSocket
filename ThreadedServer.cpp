//
// Created by Tristan Ratz on 23.04.18.
//

#include "ThreadedServer.h"

ThreadedServer::ThreadedServer(int port) : Server(port) {
    serverThreads[0] = new thread(&ThreadedServer::startAcceptLoop, this);
    serverThreads[1] = new thread(&ThreadedServer::startRecievingLoop, this);
}

void * ThreadedServer::startRecievingLoop() {
    while (true)
    {
        LinkedList<Client *>* current = cl;
        for (int i = 0; i < cl->size(); i++)
        {
            current = cl->getNext();
            if (current->getObject()->recievedData())
            {
                recievedData(current->getObject());
            }
        }
        // Hier auf empfangene Dateien und auf geschlossene Sockets schauen (deinitialisieren und
        sleep(THREAD_WAIT);
    }
}

void * ThreadedServer::startAcceptLoop() {
    while (true)
    {
        Client *c = this->acceptNewClient();

        if (cl != NULL)
        {
            cl->add(c);
        } else
        {
            cl = new ClientList(c);
        }
        sleep(THREAD_WAIT);
    }

}


void ThreadedServer::recievedData(Client *c) {
    // Here you have to write content
}
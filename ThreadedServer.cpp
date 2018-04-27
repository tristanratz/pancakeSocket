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
        function  = [] (Client *c) {};
        mainThread = std::thread(&ThreadedServer::mainThreadLoop, this);
        mainThread.detach();
    } catch (const std::exception& e) {
        perror("ERROR");
        cout << e.what();
        exit(-1);
    }
    l.info("Initialized Thread");
}

ThreadedServer::ThreadedServer(int port, std::function<void(Client *)> f) : ThreadedServer(port)
{
    function = f;
}

ThreadedServer::~ThreadedServer()
{
    //delete(function);
}


void ThreadedServer::mainThreadLoop() {
    try
    {
        for (int i = 0; i < 100; i++)
        {
            int clientSocket = this->acceptNewClient();
            if (clientSocket >= 0)
            {
                l.info("Server-Client ID: " + to_string(clientSocket));
                Client *c = new Client(clientSocket, server, this);
                l.info("Client connected");
                cl.add(*c);
                std::thread t1([=]() { this->receivingThreadLoop(cl.get(cl.getID(*c))); });
                t1.detach();
            }

            //l.ok("1: Go to sleep");
            sleep(THREAD_WAIT);
        }
    } catch (const std::exception& e) {
        perror("ERROR");
        cout << e.what();
    }
}

void ThreadedServer::receivingThreadLoop(Client *c) {
    while (c != nullptr)
    {
        function(c);
        sleep(THREAD_WAIT);
    }
}

void ThreadedServer::removeClient(Client *c) {
    l.info("Remove Client");
    this->cl.remove(cl.getID(*c));
}

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

/**
 * ThreadedServer
 *
 * Initializes and opens new multi threaded server
 *
 * @param port portNr of the server
 */
ThreadedServer::ThreadedServer(int port) : Server(port), cl() {
    l = Log("Threaded Server");
    l.info("Initializing Server...");
    try
    {
        // Is ThrededServer is initialized whithout a receiving-handler
        // The receiving handler is set to an empty function
        receiveHandler  = [] (Client &c) {};
        onConnection  = [] (Client &c, LinkedList<Client>&) {};
        onDisconnection  = [] (Client &c, LinkedList<Client>&) {};

        // Starts new thread for accepting clients
        mainThread = std::thread(&ThreadedServer::mainThreadLoop, this);
        mainThread.detach();
    } catch (const std::exception& e) {
        perror("ERROR");
        cout << e.what();
        exit(-1);
    }
    l.info("Initialized Thread");
}


/**
 * ThreadedServer
 *
 * Initializes and opens new multi threaded server
 *
 * @param port portNr of the server
 * @param f the function which will be called all the time to receive data (receiving-handler)
 */
ThreadedServer::ThreadedServer(int port, std::function<void(Client &)> f) : ThreadedServer(port)
{
    receiveHandler = f;
}

/**
 * mainThreadLoop
 *
 * the main thread loop where new clients get accepted
 */
void ThreadedServer::mainThreadLoop() {
    try
    {
        while (1)
        {
            // accepts new clients
            int clientSocket = this->acceptNewClient();
            if (clientSocket >= 0)
            {
                l.info("Server-Client ID: " + to_string(clientSocket));

                // creating new client
                Client c(clientSocket, server, this);
                l.info("Client connected");

                // client is acceptet handler gets called
                onConnection(c, cl);

                // add to the list
                cl.add(c);

                // create new thread for the client to recieve data
                std::thread t1([=]() {
                    this->receivingThreadLoop(cl.get(cl.getID(c)));
                });
                t1.detach();
            }

            sleep(THREAD_WAIT);
        }
    } catch (exception &e) {
        l.err(e.what());
    }
}

/**
 * receivingThreadLoop
 *
 * the threadLoop that will be calling the lambda function all the time
 * to receive data from Client *c
 *
 * @param c The client from which should be recieved data
 */
void ThreadedServer::receivingThreadLoop(Client &c) {
    while (c.isConnected())
    {
        // the function which should handle the receiving
        receiveHandler(c);

        sleep(THREAD_WAIT);
    }
}

/**
 * removeClient
 *
 * removes (from cl) and deinitializes client
 *
 * @param c client which should be removed
 */
void ThreadedServer::removeClient(Client &c) {
    l.info("Remove Client");
    onDisconnection(c, cl);
    this->cl.remove(cl.getID(c));
}

void ThreadedServer::setConnectionEvent(std::function<void(Client&, LinkedList<Client>&)> f)
{
    onConnection = f;
}

void ThreadedServer::setDisconnectionEvent(std::function<void(Client&, LinkedList<Client>&)> f)
{
    onDisconnection = f;
}


//
// Created by Tristan Ratz on 11.04.18.
//

#include "Server.h"
#include "config.h"
#include <errno.h>
#include <cstring>


using namespace std;

/**
* Server
*
* Initializes and opens new server
*
* @param port PortNr of the Server
*/
Server::Server(int p) : port(p)
{
    // Configuring connection options (can be changed in config.h)
    memset(&server, 0, sizeof(server));
    server.sin_family = ADRESS_TYPE;
    server.sin_addr.s_addr = htonl(RECIEVING_ADDR_SERV); // recieving IP-Adresses
    server.sin_port = htons(p);

    // Creats Server socket
    sockID = socket(ADRESS_TYPE, COMM_TYPE, 0);

    // Opens/binds server socket to the port of the machine
    if(::bind( sockID, (const struct sockaddr *)&server, sizeof(server)) < 0)
    {
        perror("Server failed");
    }

    // Creating client queue
    createClientQueue(CLIENT_QUEUE);
}

/**
 * getPort
 *
 * @return portNr of the Server
 */
int Server::getPort() const
{
    return this->port;
}

/**
 *
 * createClientQueue
 *
 * Creates an queue with the amount of clients that
 * can be waiting in the queue until they get declined
 * - is called in the server constructor
 *
 * @param waitingClients The amount of clients
 * @return -1 on error else should be == waitingClients
 */
int Server::createClientQueue(int waitingClients)
{
    return listen(sockID, waitingClients);
}

/**
 * acceptNewClient
 *
 * Blocking method which accepts a new client from the clientqueue.
 *
 * @return socket ID of a new connection point with a client
 */
int Server::acceptNewClient()
{
    sockaddr *client;
    socklen_t t = sizeof(*client);
    int c = accept(sockID, client, &t);

    if (c < 0)
        perror("Cannot connect Client");

    return c;
}
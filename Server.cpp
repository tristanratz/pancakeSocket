//
// Created by Tristan Ratz on 11.04.18.
//

#include "Server.h"
#include "config.h"

using namespace std;

Server::Server(int p) : port(p)
{
    struct sockaddr_in server;

    memset(&server, 0, sizeof(server));
    server.sin_family = ADRESS_TYPE;
    server.sin_addr.s_addr = htonl(RECIEVING_ADDR_SERV); // recieving IP-Adresses
    server.sin_port = htons(p);

    s = socket(ADRESS_TYPE, COMM_TYPE, 0);

    if(::bind( s, (struct sockaddr*)&server, sizeof( server)) < 0) {
        printf("Error: Cannot bind Server");
    }
}

int Server::getPort() const
{
    return this->port;
}

int Server::createClientQueue(int waitingClients)
{
    return listen(s, waitingClients);
}

/**
 *
 * @return new Client Connection (Socket)
 */
int Server::acceptNewClient()
{
    struct sockaddr client;
    return accept(s, (struct sockaddr*)&client, sizeof(client));
}
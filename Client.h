/**
 * Client
 *
 * The name is self explanining
 * But the class is also used by the server to communicate with each client
 * Created by Pancake Software, Tristan Ratz on 23.04.18.
 */

#ifndef PANCAKESOCKET_CLIENT_H
#define PANCAKESOCKET_CLIENT_H

#include <stdlib.h>
#include <string>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <netdb.h>
#include "config.h"

using namespace std;


class Client
{
    public:
        Client(int socket, sockaddr_in server);
        Client(const char *hostname, long portno);

        void closeSocket();
        bool connectSocket();

        bool sendText(const char *text);
        bool sendData(const void *data);

        bool recievedData();
        bool socketClosed();

        char * recieve();

        static char * getHostnameByDomain(const char *domain);

    protected:
        int sockID;
        int recLen;
        Log l;
        sockaddr_in serv_addr;
        char recData[BUFFER_SIZE];
        bool sockClosed;
};


#endif //PANCAKESOCKET_CLIENT_H

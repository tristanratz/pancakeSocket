//
// Created by Tristan Ratz on 11.04.18.
//

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

using namespace std;


class Client
{
    public:
        Client(int socket, sockaddr_in server);
        Client(const char *domain);
        Client(const char *hostname, long portno);

        void closeSocket();
        bool connectSocket();

        bool sendText(const char *text);
        bool sendData(const void *data);

        bool recievedData();
        bool socketClosed();

        char recieve();

        static char * getHostnameByDomain(const char *domain);

    protected:
        int sockID;
        sockaddr_in serv_addr;
        char recData;
        bool sockClosed;
};


#endif //PANCAKESOCKET_CLIENT_H

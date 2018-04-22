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
        Client(const char *domain);
        Client(const char *hostname, long portno);

        int getID() const;
        void closeSocket();
        bool connectSocket();

        bool sendText(const char *text);
        bool sendData(const void *data);

        char recieve();

        static char * getHostnameByDomain(const char *domain);

    private:
        int id;
        int serverPort;
        int sockID;
        sockaddr_in serv_addr;
        char recievedData;
};


#endif //PANCAKESOCKET_CLIENT_H

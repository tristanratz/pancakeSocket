//
// Created by Tristan Ratz on 11.04.18.
//

#ifndef PANCAKESOCKET_SERVER_H
#define PANCAKESOCKET_SERVER_H

#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string>

using namespace std;


class Server
{
    public:
        Server(const char *name);
        string gethostname() const;


    private:
        string name;
        int portno;
        hostent* h;

};


#endif //PANCAKESOCKET_SERVER_H

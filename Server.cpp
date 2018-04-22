//
// Created by Tristan Ratz on 11.04.18.
//

#include <netdb.h>
#include <iostream>
#include "Server.h"

using namespace std;

Server::Server(const char *hostname) : name(hostname)
{
    h = gethostbyname(hostname);

    if (!h) {
        printf("Error");
    }

    cout << "hlength: " << h->h_length << "\n";
}

string Server::gethostname() const
{
    return name;
}
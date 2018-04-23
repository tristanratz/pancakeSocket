//
// Created by Tristan Ratz on 23.04.18.
//

#ifndef PANCAKESOCKET_CONFIG_H
#define PANCAKESOCKET_CONFIG_H

#include <sys/types.h>

static const int ADRESS_TYPE = AF_INET6; //IPv6
static const int COMM_TYPE = SOCK_STREAM; // TCP
static const int RECIEVING_ADDR_SERV = INADDR_ANY; // The Adresses which the server can recieve from (intra-, internet...)
static const int ALLOWED_CLIENTS_WAITING = 10; // How many Clients are allowed in the queue until they get declined

#endif //PANCAKESOCKET_CONFIG_H

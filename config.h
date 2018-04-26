/**
 * Config.h
 *
 * Created by Pancake Software, Tristan Ratz on 23.04.18.
 *
*/

#ifndef PANCAKESOCKET_CONFIG_H
#define PANCAKESOCKET_CONFIG_H

#include <sys/types.h>
#include "Log/Log.h"

static const int ADRESS_TYPE = AF_INET; //IPv6
static const int COMM_TYPE = SOCK_STREAM; // TCP
static const int RECIEVING_ADDR_SERV = INADDR_ANY; // The Addresses which the server can receive from (intra-, internet...)
static const int CLIENT_QUEUE = 10; // How many Clients are allowed in the queue until they get declined
static const int BUFFER_SIZE = 1024; // Size of the receiving buffer
static const float THREAD_WAIT = 1; // (Seconds) So that the thread is not taking to much time

#endif //PANCAKESOCKET_CONFIG_H

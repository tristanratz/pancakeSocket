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
#include <cstring>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <netdb.h>
#include "config.h"
class ThreadedServer;

using namespace std;


class Client
{
    public:
        /**
         *
         * @param socket If there is a existing socket sockID
         * @param server Configuration of the connection
         * @param delegate The delegate
         */
        Client(int socket, sockaddr_in &server, ThreadedServer *delegate);

        /**
         * Client
         *
         * Standard way of creating a client
         *
         * @param hostname An IP Adress to connect to
         * @param portno The port number to connect to
         */
        Client(const char *hostname, long portno);


        /**
         * connectSocket
         * Connecting socket to server
         *
         * @return true on success
         */
        bool connectSocket();

        /**
         * closeSocket
         * Closing socket and deleting itself
         */
        void closeSocket();

        /**
         * sendText
         * Sending a string
         *
         * @param data
         * @return true on success
         */
        bool sendText(const string data);


        /**
         * sendData
         * Send data
         *
         * @param data
         * @return true on sucess
         */
        bool sendData(const char *data);

        /**
        * isConnected
        *
        * @return true when connected
        */
        bool isConnected();

        /**
         * receive
         * Blocking function wich returns a string with the received data
         *
         * @return recieved string
         */
        string receive();

        /**
         * getHostnameByDomain
         * Returns an ip adress of you submit an domain (i.e. localhost)
         *
         * @param domain
         * @return An ip adress
         */
        static char * getHostnameByDomain(const char *domain);

        bool operator != (const Client &c) const
        {
                return c.sockID != this->sockID;
        }

    protected:
        int sockID;                 // socket
        Log l;                      // A Logger
        sockaddr_in serv_addr;      // The client config
        bool connected;             // If it is connected
        ThreadedServer *delegate;   // Delegate, where it has to be deleted on socket closure
};


#endif //PANCAKESOCKET_CLIENT_H

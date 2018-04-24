//
// Created by Tristan Ratz on 11.04.18.
//


#include <arpa/inet.h>
#include "Client.h"
#include "config.h"

static int idCount = 0;

Client::Client(int socket, sockaddr_in server) : sockID(socket), serv_addr(server) {

}

Client::Client(const char *hostname, long int portno)
{
    sockID = socket(ADRESS_TYPE, COMM_TYPE, 0);
    sockClosed = false;

    if (sockID < 0)
        perror("ERROR opening socket");

    serv_addr = sockaddr_in();

    in_addr_t ia = inet_addr(hostname);
    memcpy((char*)&serv_addr.sin_addr, &ia, sizeof(ia)); //copies the value of the second argument to the first for (third argument) bytes

    serv_addr.sin_family = COMM_TYPE;
    serv_addr.sin_port = htonl(portno);

}

bool Client::sendText(const char *text)
{
    return sendData(text);
}

bool Client::sendData(const void *data)
{
    int x = send(sockID, data, sizeof(data), 0);
    if (x < 0) {
        perror("Error beim senden der Daten");
        return false;
    } else if (x < sizeof(data)) {
        perror("Nicht alle Daten wurden versendet");
        return false;
    }
    return true;
}

void Client::closeSocket()
{
    close(this->sockID);
    sockClosed = true;
}

bool Client::connectSocket()
{
    if (connect(this->sockID, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
        return false;
    }
    return true;
}

char Client::recieve()
{
    recv(sockID, (char *)recData, sizeof(recData), 0);

    return recData;
}

char* Client::getHostnameByDomain(const char *domain)
{
    return gethostbyname(domain)->h_name;
}

bool Client::socketClosed()
{
    return sockClosed;
}

bool Client::recievedData()
{
    return false;
}
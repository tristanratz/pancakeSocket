//
// Created by Tristan Ratz on 11.04.18.
//


#include <arpa/inet.h>
#include "Client.h"
#include "config.h"

static int idCount = 0;

Client::Client(const char *hostname, long int portno) : id(idCount)
{
    idCount++;
    sockID = socket(ADRESS_TYPE, COMM_TYPE, 0);

    if (sockID < 0)
        perror("ERROR opening socket");

    serv_addr = sockaddr_in();

    in_addr_t ia = inet_addr(hostname);
    memcpy((char*)&serv_addr.sin_addr, &ia, sizeof(ia)); //copies the value of the second argument to the first for (third argument) bytes

    serv_addr.sin_family = COMM_TYPE;
    serv_addr.sin_port = htonl(portno);

}

int Client::getID() const
{
    return id;
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
    recv(sockID, (char *)recievedData, sizeof(recievedData), 0);

    return recievedData;
}

char* Client::getHostnameByDomain(const char *domain)
{
    return gethostbyname(domain)->h_name;
}
//
// Created by Tristan Ratz on 11.04.18.
//


#include <arpa/inet.h>
#include "Client.h"
#include <cstring>
#include "ThreadedServer.h"

static int idCount = 0;

Client::Client(int socket, sockaddr_in server, ThreadedServer *tS) : sockID(socket), serv_addr(server) , l("Client"), delegate(tS) {
    connected = false;
}

Client::Client(const char *hostname, long int portno) : l("Client"), delegate(nullptr)
{
    sockID = socket(ADRESS_TYPE, COMM_TYPE, 0);
    connected = false;

    if (sockID < 0)
        perror("ERROR opening socket");

    //serv_addr = sockaddr_in();
    memset( &serv_addr, 0, sizeof (serv_addr));

    in_addr_t ia = inet_addr(hostname);
    memcpy((char*)&serv_addr.sin_addr, &ia, sizeof(ia)); //copies the value of the second argument to the first for (third argument) bytes

    serv_addr.sin_family = ADRESS_TYPE;
    serv_addr.sin_port = htons(portno);
}

bool Client::connectSocket()
{
    if (connect(this->sockID, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
        l.warn("Unable to connect to server.");
        perror("Connection not found");
        return false;
    }
    connected = true;
    l.info("Connected.");

    return true;
}

bool Client::sendText(const char *data)
{
    int x = send(sockID, data, sizeof(data), 0);
    if (x != sizeof(data)) {
        perror("Error beim senden der Daten");
        return false;
    } else if (x < sizeof(data)) {
        perror("Nicht alle Daten wurden versendet");
        return false;
    }

    //l.info("Sended Data: " + string(data));
    return true;
}

bool Client::sendData(const void *data)
{
    return false;
}

void Client::closeSocket()
{
    close(this->sockID);
    connected = false;
    if (delegate != nullptr)
        delegate->removeClient(this);
}

string Client::receive()
{
    char* recData[BUFFER_SIZE];
    l.info("Recieving Data...");
    int r;
    if (connected)
        r = recv(sockID, recData, BUFFER_SIZE, 0);
    if (r > 0 && r < BUFFER_SIZE)
    {
        recData[r] = (char *)'\0';
        return string(*recData);
    } else if (r == 0)
        closeSocket();
    else
        perror("Can not receive Data");

    return string();
}

char* Client::getHostnameByDomain(const char *domain)
{
    return gethostbyname(domain)->h_name;
}

bool Client::isConnected()
{
    return connected;
}
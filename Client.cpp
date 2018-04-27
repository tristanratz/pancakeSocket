//
// Created by Tristan Ratz on 11.04.18.
//


#include <arpa/inet.h>
#include "Client.h"
#include "ThreadedServer.h"

static int idCount = 0;

Client::Client(int socket, sockaddr_in &server, ThreadedServer *tS) : sockID(socket), serv_addr(server) , l("Client"), delegate(tS) {
    connected = true;
}

Client::Client(const char *hostname, long int portno) : l("Client"), delegate(nullptr)
{
    sockID = socket(ADRESS_TYPE, COMM_TYPE, 0);
    l.info("Client-Client ID: " + to_string(sockID));
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

bool Client::sendText(const string data)
{

    return sendData((char *)data.c_str());


}

bool Client::sendData(const char *data)
{
    int x;

    if (connected)
        x = send(sockID, data, strlen(data), 0);
    else
        return false;

    if (x < 0) {
        perror("Could not send any Data");
        return false;
    } else if (x < sizeof(data)) {
        perror("Could not send all data");
        return false;
    }

    l.info("Sended Data: " + string((char*)data));
    return true;
}

void Client::closeSocket()
{
    close(this->sockID);
    connected = false;
    if (delegate != nullptr)
        delegate->removeClient(this);
}

string * Client::receive()
{

    if (connected)
    {
        int r;
        char recData[BUFFER_SIZE];
        r = recv(sockID, recData, BUFFER_SIZE, 0);
        if (r > 0 && r < BUFFER_SIZE)
        {
            //recData[r] = '\0';
            return new string(recData);
        } else if (r == 0)
            closeSocket();
        else
            perror("Can not receive Data");
    }
    return new string();
}

char* Client::getHostnameByDomain(const char *domain)
{
    return gethostbyname(domain)->h_name;
}

bool Client::isConnected()
{
    return connected;
}
//
// Created by Tristan Ratz on 11.04.18.
//


#include <arpa/inet.h>
#include "Client.h"
#include "ThreadedServer.h"

static int idCount = 0;
/**
 *
 * @param socket If there is a existing socket sockID
 * @param server Configuration of the connection
 * @param delegate The delegate
 */
Client::Client(int socket, sockaddr_in &server, ThreadedServer *delegate) : sockID(socket), serv_addr(server) , l("Client"), delegate(delegate) {
    // Already connected and in use with the server
    connected = true;
}

/**
 * Client
 *
 * Standard way of creating a client
 *
 * @param hostname An IP Adress to connect to
 * @param portno The port number to connect to
 */
Client::Client(const char *hostname, long int portno) : l("Client"), delegate(nullptr)
{
    // Opening socket
    sockID = socket(ADRESS_TYPE, COMM_TYPE, 0);
    l.info("Client-Client ID: " + to_string(sockID));

    // Not yet connected
    connected = false;

    // Look for success
    if (sockID < 0)
        perror("ERROR opening socket");

    // Configuring socket options
    serv_addr = sockaddr_in();
    memset( &serv_addr, 0, sizeof (serv_addr));

    in_addr_t ia = inet_addr(hostname);

    //copies the value of the second argument to the first for (third argument) bytes
    memcpy((char*)&serv_addr.sin_addr, &ia, sizeof(ia));

    serv_addr.sin_family = ADRESS_TYPE;
    serv_addr.sin_port = htons(portno);
}

/**
 * connectSocket
 * Connecting socket to server
 *
 * @return true on success
 */
bool Client::connectSocket()
{
    if (connected)
        return true;

    // Connecting socket to server
    if (connect(this->sockID, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
        l.warn("Unable to connect to server.");
        perror("Connection not found");
        return false;
    }
    // Now  it is connected
    connected = true;
    l.info("Connected.");

    return true;
}

/**
 * sendText
 * Sending a string
 *
 * @param data
 * @return true on success
 */
bool Client::sendText(const string data)
{

    return sendData((char *)data.c_str());

}

/**
 * sendData
 * Send data
 *
 * @param data
 * @return true on sucess
 */
bool Client::sendData(const char *data)
{
    int sendSize;

    if (connected)
        sendSize = send(sockID, data, strlen(data), 0);
    else
        return false;

    if (sendSize < 0) {
        perror("Could not send any Data");
        return false;
    } else if (sendSize < sizeof(data)) {
        perror("Could not send all data");
        return false;
    }

    l.info("Sended Data: " + string((char*)data));
    return true;
}

/**
 * closeSocket
 * Closing socket and deleting itself
 */
void Client::closeSocket()
{
    close(this->sockID);
    connected = false;
    if (delegate != nullptr)
        delegate->removeClient(*this);
}

/**
 * receive
 * Blocking function wich returns a string with the received data
 *
 * @return recieved string
 */
string  Client::receive()
{

    if (connected)
    {
        int receiveSize;
        char recData[BUFFER_SIZE];
        receiveSize = recv(sockID, recData, BUFFER_SIZE, 0);
        if (receiveSize > 0 && receiveSize < BUFFER_SIZE)
        {
            //recData[receiveSize] = '\0';
            return string(recData);
        } else if (receiveSize == 0)
            closeSocket();
        else
            perror("Can not receive Data");
    }
    return string();
}

/**
 * getHostnameByDomain
 * Returns an ip adress of you submit an domain (i.e. localhost)
 *
 * @param domain
 * @return An ip adress
 */
char* Client::getHostnameByDomain(const char *domain)
{
    return gethostbyname(domain)->h_name;
}

/**
 * isConnected
 *
 * @return true when connected
 */
bool Client::isConnected()
{
    return connected;
}
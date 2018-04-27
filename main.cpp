#include <iostream>
#include <signal.h>
#include "ThreadedServer.h"
#include "Client.h"

char* receive(int cl);

int main() {
    Log l = Log("main");
    l.ok("Started");
    int port = 2001;

    void (*respond_function) (Client*) = [] (Client *c) {
        Log log = Log("Server-Resp");
        string *receivedData = c->receive();
        // Here you have to write content
        log.info("Client Message: " + *receivedData);

        string datatosend = "What does \"" + *receivedData + "\" mean?";
        log.ok("Server sends!");
        sleep(1);
        c->sendText(datatosend);
    };

    ThreadedServer a(port, respond_function);

    Client c = Client("127.0.0.1", port);
    c.connectSocket();

    sleep(1);

    l.ok("Client sends!");
    c.sendText("Hello World!");
    sleep(1);
    l.info("Client recieved: " + *c.receive());

    sleep(1);

    l.ok("Client sends!");
    c.sendText("Hello World again!");
    sleep(1);
    l.info("Client recieved: " + *c.receive());

    while(1) {}
}
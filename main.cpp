#include <iostream>
#include <signal.h>
#include "ThreadedServer.h"
#include "Client.h"

int main(int argc, char **argv)
{
    int port = 7575;

    Log l = Log("main");
    l.ok("Started");
    ThreadedServer a(port);
    l.ok("Initialized Threaded Server");
    Client c = Client("127.0.0.1", port);
    sleep(1);
    c.connectSocket();

    int i = 0;
    while (true){
        string s = "Hello World! Nr. " + to_string(i);
        i++;
        //l.info(s);
        c.sendText("WHOOP");
        sleep(THREAD_WAIT);

    }
    return 0;
}
#include <iostream>
#include "ThreadedServer.h"
#include "Client.h"

int main()
{
    Log l = Log("main");
    l.ok("Started");
    int p = 1999;
    ThreadedServer(1999);
    l.ok("Initialized Threaded Server");
    Client c = Client("127.0.0.1", 1999);
    sleep(1);
    c.connectSocket();

    l.ok("Terminated");
    int i = 0;
    while (true){
        string s = "Hello World! Nr. " + to_string(i);
        i++;
        l.info(s);
        c.sendText(s.c_str());
        sleep(THREAD_WAIT);

    }
    return 0;
}
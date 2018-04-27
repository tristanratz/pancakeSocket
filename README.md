# pancakeSocket
Server Client Library (UNIX only at the moment)

Made with love and pancakes

## Usage
How to use it 
1. Initialize a Client-Object with IP-Adress, Port Number of the Server.
2. Initialize a Server-Object with the Port which should be open and a function which should be started as a thread to recieve data from the client.
3. Use the parameter (Client \* c) has  of your function to communicate with the client
4. To communicate just call one of these functions:

```
bool Client::sendText(string data)
bool Client::sendData(const char *data)
string Client::receive()
```

## Sample
Here is a simple example of the usage, which also can be found in the main.cpp:

**Server:**
```
int port = 1997;

void (*respond_function) (Client*) = [] (Client *c) 
{
  string *receivedData = c->receive();
  cout << receivedData;
  
  string datatosend = "What does \"" + *receivedData + "\" mean?";  
  c->sendText(datatosend);
};

ThreadedServer a(port, respond_function);
```

**Client:**
```
Client c = Client("127.0.0.1", port);
c.connectSocket();

c.sendText("Hello World!");
cout << *c.receive() << "\n";

cout <c.sendText("Hello World again!");
cout << *c.receive() << "\n";
    
```
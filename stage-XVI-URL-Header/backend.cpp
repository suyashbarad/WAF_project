#include <iostream>
#include <string>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>

using namespace std;

int main()
{
    char buffer[1024];

    // Create Socket
    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);

    if(serverSocket == -1)
    {
        cout<<"Unable to create socket"<<endl;
        return 1;
    }

    cout<<"Backend socket created successfully"<<endl;

    // Server Address
    sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    serverAddress.sin_port = htons(9090);

    // Bind
    if(::bind(serverSocket,
              (sockaddr*)&serverAddress,
              sizeof(serverAddress)) < 0)
    {
        cout<<"Bind failed: "<<strerror(errno)<<endl;
        return 1;
    }

    cout<<"Backend bind successful!"<<endl;

    // Listen
    if(listen(serverSocket,5) < 0)
    {
        cout<<"Listen failed"<<endl;
        return 1;
    }

    cout<<"Backend server listening on port 9090..."<<endl;

    while(true)
    {
        int clientSocket = accept(serverSocket,NULL,NULL);

        if(clientSocket < 0)
        {
            cout<<"Accept failed"<<endl;
            continue;
        }

        cout<<"\nClient Connected"<<endl;

        // Clear buffer
        memset(buffer,0,sizeof(buffer));

        // Receive request
        recv(clientSocket,
             buffer,
             sizeof(buffer),
             0);

        string request = buffer;

        cout<<"Received Request:"<<endl;
        cout<<request<<endl;

        // Send response
        string response = "HTTP/1.1 \n200 OK\n\nWelcome to Backend Server!";

        send(clientSocket,
             response.c_str(),
             response.length(),
             0);

        cout<<"Response Sent"<<endl;

        close(clientSocket);

        cout<<"Client Disconnected"<<endl;
    }

    close(serverSocket);

    return 0;
}
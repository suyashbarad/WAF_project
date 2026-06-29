#include <iostream>
#include <sys/socket.h>     //for socket functions
#include <arpa/inet.h>      //for knowing IP
#include <unistd.h>         //for closing socket
#include <cstring>   // add this header

using namespace std;

int main(){
    char buffer[1024] = {0};
    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    int clientSocket;
    if(serverSocket == -1){
        cout<<"Unable to open socket"<<endl;
        return 1;
    }
    else{
        cout<<"Socket opened successfully"<<endl;
    }
    sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    serverAddress.sin_port = htons(8080);
    
    if(::bind(serverSocket,
        (sockaddr*)&serverAddress,
        sizeof(serverAddress)) < 0)
    {
        cout<<"Bind failed: "<<strerror(errno)<<endl;
        return 1;
    }   
    else{
        cout<<"\nBind successful! "<<endl;
    }
    if(listen(serverSocket, 5) < 0){
        cout<<"Listen failed"<<endl;
        return 0;
    }
    else{
        cout<<"Server is listening...";
    }
    cout << "\nWaiting for a client to connect...\n" << endl;

    clientSocket = accept(serverSocket, NULL, NULL);

    if(clientSocket < 0){
        cout<<"Accept failed"<<endl;
        return 1;
    }
    else{
        cout<<"CLient connected! "<<endl;
    }
    recv(clientSocket, buffer, sizeof(buffer), 0);
    cout<<"Recieved request from client"<<endl<<endl;

    string response = "HTTP/1.1 200 OK";
    send(clientSocket, response.c_str(), response.length(), 0);
    cout<<"Response sent! "<<endl;
    close(clientSocket);
    close(serverSocket);
    return 0;
}
//to run the code ithout failure
//run this - lsof -i :8080
//you'll get a PID number then paste it into - kill -9 PID

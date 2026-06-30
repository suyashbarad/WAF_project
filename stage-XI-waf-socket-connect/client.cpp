#include <iostream>
#include <sys/socket.h>     //for socket functions
#include <arpa/inet.h>      //for knowing IP
#include <unistd.h>         //for closing socket
#include <cstring>   // add this header

using namespace std;

int main(){
    char buffer[1024];
    int clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if(clientSocket == -1){
        cout<<"Unable to open socket"<<endl;
        return 1;
    }
    else{
        cout<<"Socket opened successfully"<<endl;
    }
    sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(8080);

    inet_pton(AF_INET, "127.0.0.1", &serverAddress.sin_addr);

    if(::connect(clientSocket,
        (sockaddr*)&serverAddress,
        sizeof(serverAddress)) < 0)
    {
        cout<<"connection failed: "<<strerror(errno)<<endl;
        return 1;
    }   
    else{
        cout<<"\nconnection successful! "<<endl;
    }
    string request;
    cout<<"Enter request: ";
    getline(cin, request);
    send(clientSocket, request.c_str(), request.length(), 0);
    cout<<"Request sent to server"<<endl<<endl;

    recv(clientSocket, buffer, sizeof(buffer), 0);
    cout<<"Server replied: "<<buffer<<endl;
    close(clientSocket);
    return 0;
}
//to run the code ithout failure
//run this - lsof -i :8080
//you'll get a PID number then paste it into - kill -9 PID

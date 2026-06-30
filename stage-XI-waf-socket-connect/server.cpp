#include<iostream>
#include<string>
#include<fstream>
#include<sstream>
#include <sys/socket.h>     //for socket functions
#include <arpa/inet.h>      //for knowing IP
#include <unistd.h>         //for closing socket
#include <cstring>   // add this header
#include<map>

// #define MAX_ATTACKS 3
using namespace std;
  
bool isSQL_XSS_Inject(string req){
    ifstream sql_XSS_File("rules.txt");

    if(!sql_XSS_File.is_open()){
        cout<<"Unable to open rules.txt"<<endl;
        return false;
    }
    string rule;
    while(getline(sql_XSS_File, rule)){
        if(req.find(rule) != string::npos){
            return true;
        }
    }
    return false;  
}
int main(){
    ofstream log("log.txt", ios::app);   //continuous appends all the readed data inot log file
    string line;                         //without erasing the old data
    
    ofstream backend("backend.txt", ios::app);    //for passed files
    backend<<"--------------Backend Files----------------\n\n-------------------------------------------\n";
    if(!backend.is_open()){
        cout<<"Unable to open backend.txt"<<endl;
        return 1;
    }
    ifstream config("config.txt");          //to get max attacks count configuration
    string config_line;
    if(!config.is_open()){
        cout<<"Unable to open config.txt"<<endl;
        return 1;
    }
    getline(config, config_line);
    stringstream conf(config_line);
    string key, value;
    getline(conf, key, '=');
    getline(conf, value);

    int MAX_ATTACKS = stoi(value);
    map <string, int> ipcount;  
    char buffer[1024];
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
    while(true){
        clientSocket = accept(serverSocket, NULL, NULL);

        if(clientSocket < 0){
            cout<<"Accept failed"<<endl;
            return 1;
        }
        else{
            cout<<"CLient connected! "<<endl;
        }
        memset(buffer, 0, sizeof(buffer));
        recv(clientSocket, buffer, sizeof(buffer), 0);

        stringstream ss(line);           //stringstream extracts first string of line and names it as "line";
        
        string ip;
        ss >> ip;
        string request = buffer;
        
        cout<<"Recieved request from client"<<endl<<endl;
            if(isSQL_XSS_Inject(request)){

                ipcount[ip]++;

                log<<"IP: "<<ip<<endl;
                log<<"Request == ( "<< request << " ) " << endl;
                log<<"Status: Blocked"<<endl;
                log<<"Times attacked: "<<ipcount[ip]<<endl;
                log<<"-------------------------------------------\n";
                if(ipcount[ip] >= MAX_ATTACKS){
                    log<<"Blocked: "<<ip<<" attacked more than "<< MAX_ATTACKS <<" times ("<<ipcount[ip]<<" times)"<<endl;
                    log<<"-------------------------------------------\n";
                    close(clientSocket);
                    continue;
                }
                string response = "http/1.1 403 forbidden";
                send(clientSocket, response.c_str(), response.length(), 0);
                close(clientSocket);
                cout<<"Request blocked"<<endl;
            }
            else{
                log<<"IP: "<<ip<<endl;
                log<<"Request == ( "<< request << " ) " << endl;
                log<<"Status: Safe"<<endl;
                backend<<"IP: "<<ip<<endl;
                backend<<"Request recieved == ( "<< request << " ) " << endl;
                backend<<"-------------------------------------------\n";
                log<<"-------------------------------------------\n";
                string response = "Forwarded to backend";
                send(clientSocket, response.c_str(), response.length(), 0);
                cout<<"Request accepted"<<endl;
            }
        }
        
    log<<"\n--------------Attack Summary----------------\n";

    for(auto x: ipcount){
        if(ipcount[x.first] < MAX_ATTACKS){
            log<<x.first<<" == "<<x.second<<" times"<<endl;
        }
        else{
            log<<x.first<<" == "<<x.second<<" times -- WARNING exceeded "<< MAX_ATTACKS <<" attacks"<<endl;
        }
    }
    return 0;
}

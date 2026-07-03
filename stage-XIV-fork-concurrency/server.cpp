#include <iostream>
#include <regex>
#include <string>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <sys/types.h>      //for fork
#include <sys/wait.h>      //for fork
#include <sys/socket.h>     //for socket functions
#include <arpa/inet.h>      //for knowing IP
#include <unistd.h>         //for closing socket
#include <cstring>   // add this header
#include <map>

// #define MAX_ATTACKS 3
using namespace std;
  
const int MAX_REQ_SIZE = 2048;
string ip = "127.0.0.1";
bool isSQL_XSS_Inject(string req){
    ifstream sql_XSS_File("rules.txt");

    if(!sql_XSS_File.is_open()){
        cout<<"Unable to open rules.txt"<<endl;
        return false;
    }
    string rule;
    cout << "Request = [" << req << "]" << endl;

    while(getline(sql_XSS_File, rule))
    {
        cout << "Rule = [" << rule << "]" << endl;

        regex pattern(rule, regex_constants::icase);
        if(regex_search(req, pattern)){
            cout << "MATCH FOUND!" << endl;
            return true;
        }
    }

        cout << "NO MATCH FOUND" << endl;
        return false;
    }
bool validRequest(string method){
    return method=="GET" ||
           method=="get" ||
           method=="POST" ||
           method=="post" ||
           method=="PUT" ||
           method=="put" ||
           method=="DELETE" ||
           method=="delete";
}
string getCurrentTime()
{
    time_t now = time(0);
    tm *ltm = localtime(&now);
    stringstream ss;
    ss << put_time(ltm, "%Y-%m-%d %H:%M:%S");
    return ss.str();
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
    map <string, bool> blockedIP;  
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
        while(waitpid(-1, NULL, WNOHANG) > 0);
        clientSocket = accept(serverSocket, NULL, NULL);

        if(clientSocket < 0){
            cout<<"Accept failed"<<endl;
            continue;
        }

        pid_t pid = fork();

        if(pid < 0){
            cout << "Fork failed!" << endl;
            close(clientSocket);
            continue;
        }
        if(pid > 0){   // Parent process
            close(clientSocket);
            wait(NULL);          // Wait for child to finish
            close(serverSocket); // Close listening socket
            break;               // Exit while loop
        }
        close(serverSocket);
        cout<<"CLient connected! "<<endl;
        memset(buffer, 0, sizeof(buffer));
        recv(clientSocket, buffer, sizeof(buffer), 0);

        
        string request = buffer;
        cout << "Request received by WAF: " << request << endl;
        stringstream parser(request);           //stringstream extracts first string of line and names it as "line";
        
        string method;
        parser >> method;

        string path;
        getline(parser, path);

        if(request.length() > MAX_REQ_SIZE){
            log<<"========================================"<<endl;
            log<<"Time   : "<<getCurrentTime()<<endl;
            log<<"IP     : "<<ip<<endl;
            log<<"Method : "<<method<<endl;
            log<<"Request: "<<path<<endl;
            log<<"Status : Blocked"<<endl;
            log<<"Action : Size exceed"<<endl;
            log << "Request size = " << request.length() << endl;
            log<<"========================================"<<endl;
            string response = "HTTP/1.1 413 Payload Too Large";
            send(clientSocket,
                response.c_str(),
                response.length(),
                0);

            close(clientSocket);
            exit(0);
        }
        // Remove leading space
        if(!path.empty() && path[0] == ' ')
            path.erase(0, 1);

        cout<<"\n--------------Parser request----------------\n";
        cout << "IP: " << ip << endl;
        cout << "Method  = [" << method << "]" << endl;
        cout << "Path    = [" << path << "]" << endl;
        cout<<"Recieved request from client"<<endl<<endl;

        if(!validRequest(method)){
            log<<"========================================"<<endl;
            log<<"Time   : "<<getCurrentTime()<<endl;
            log<<"IP     : "<<ip<<endl;
            log<<"Method : "<<method<<endl;
            log<<"Request: "<<path<<endl;
            log<<"Status : Invalid Request"<<endl;
            log << "Request size = " << request.length() << endl;
            log<<"========================================"<<endl;
            string response = "HTTP/1.1 400 Bad Request";
            send(clientSocket,
                response.c_str(),
                response.length(),
                0);

            close(clientSocket);
            exit(0);
        }
        if(blockedIP[ip]){
            log<<"========================================"<<endl;
            log<<"Time   : "<<getCurrentTime()<<endl;
            log<<"IP     : "<<ip<<endl;
            log<<"Method : "<<method<<endl;
            log<<"Request: "<<path<<endl;
            log<<"Status : Blocked"<<endl;
            log<<"Times blocked: "<<blockedIP[ip]<<endl;
            log << "Request size = " << request.length() << endl;
            log<<"========================================"<<endl;

            cout<<"IP address is blocked";
            string response = "http/1.1 403 forbidden\nIP BLOCKED\n";
            send(clientSocket, response.c_str(), response.length(), 0);
            close(clientSocket);
            exit(0);
        }
        cout << "Path being checked = [" << path << "]" << endl;
        if(isSQL_XSS_Inject(path)){

            ipcount[ip]++;

            log<<"========================================"<<endl;
            log<<"Time   : "<<getCurrentTime()<<endl;
            log<<"IP     : "<<ip<<endl;
            log<<"Method : "<<method<<endl;
            log<<"Request: "<<path<<endl;
            log<<"Status : Blocked"<<endl;
            log<<"Times blocked: "<<blockedIP[ip]<<endl;
            log << "Request size = " << request.length() << endl;
            log<<"========================================"<<endl;
            if(ipcount[ip] >= MAX_ATTACKS){
                log<<"Blocked: "<<ip<<" attacked more than "<< MAX_ATTACKS <<" times ("<<ipcount[ip]<<" times)"<<endl;
                log<<"-------------------------------------------\n";
                close(clientSocket);
                exit(0);
            }
            string response = "http/1.1 403 forbidden\nAttack try\n";
            send(clientSocket, response.c_str(), response.length(), 0);
            close(clientSocket);
            cout<<"Request blocked"<<endl;
            exit(0);
        }
        else{
            log<<"========================================"<<endl;
            log<<"Time   : "<<getCurrentTime()<<endl;
            log<<"IP     : "<<ip<<endl;
            log<<"Method : "<<method<<endl;
            log<<"Request: "<<path<<endl;
            log<<"Status : Safe"<<endl;
            log << "Request size = " << request.length() << endl;
            log<<"========================================"<<endl;
            int backendSocket = socket(AF_INET, SOCK_STREAM, 0);
            if(backendSocket == -1){
                cout<<"Unable to open socket";
            }
            else{
                sockaddr_in backendAddress;

                backendAddress.sin_family = AF_INET;
                backendAddress.sin_port = htons(9090);
                backendAddress.sin_addr.s_addr = inet_addr("127.0.0.1");

                inet_pton(AF_INET, "127.0.0.1", &backendAddress.sin_addr);

                if(::connect(backendSocket, (sockaddr*)&backendAddress, sizeof(backendAddress)) < 0){

                    cout<<"connection failed!"<<strerror(errno)<<endl;
                    string response = "http/1.1 500 internal server error";
                    send(clientSocket, request.c_str(), request.length(), 0);

                    return 1;
                }   
                else{
                    send(backendSocket, request.c_str(), request.length(), 0);
                    cout<<"connection Successful !"<<endl;
                    char backendBuffer[1024];

                    memset(backendBuffer, 0, sizeof(backendBuffer));
                    recv(backendSocket, backendBuffer, sizeof(backendBuffer), 0);
                    cout<<"Request recieves from user"<<endl;

                    send(clientSocket, backendBuffer, strlen(backendBuffer), 0);
                    cout<<"Safe request forwarded successfully! "<<endl;
                    close(backendSocket);
                }

            }
            log<<"-------------------------------------------\n";
            close(clientSocket);
            exit(0);
        }
        if(ipcount[ip] >= MAX_ATTACKS){
            blockedIP[ip] = true;
            cout<<"IP BLACKLISTED"<<endl;
        }

        close(clientSocket);
        exit(0);
    }
    
        
    // log<<"\n--------------Attack Summary----------------\n";

    for(auto x: ipcount){
        if(ipcount[x.first] < MAX_ATTACKS){
            log<<x.first<<" == "<<x.second<<" times"<<endl;
        }
        else{
            blockedIP[x.first] = true;
            cout<<"\n============================\n";
            cout<<"IP BLACKLISTED"<<endl;
            cout<<x.first<<endl;
            cout<<"============================\n";

            log<<"\n============================\n";
            log<<"IP BLACKLISTED"<<endl;
            log<<x.first<<endl;
            log<<"============================\n";

            log<<"STATUS : BLACKLISTED"<<endl;
            log<<x.first<<" == "<<x.second<<" times -- WARNING exceeded "<< MAX_ATTACKS <<" attacks"<<endl;
        }
    }
    return 0;
}
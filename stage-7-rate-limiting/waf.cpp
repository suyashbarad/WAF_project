#include<iostream>
#include<string>
#include<fstream>
#include<sstream>
#include<map>

// #define MAX 100
using namespace std;
  
bool isSQL_Inject(string req){                                  //hacker tries for SQL injection that is bypass login
    if(req.find("OR 1=1") != string::npos) return true;
    if(req.find("'--") != string::npos) return true;
    if(req.find("SELECT * FROM") != string::npos) return true;     //added advanced security
    if(req.find("UNION SELECT") != string::npos) return true;
    if(req.find("DROP TABLE") != string::npos) return true;
    return false;
}
bool isXSS(string req){                                  //hacker tries for XSS injection that is running JS into code
    if(req.find("<script>") != string::npos) return true;
    if(req.find("javascript:") != string::npos) return true;
    return false;
}
int main(){
    ifstream file("request.txt");
    ofstream log("log.txt", ios::app);   //continuous appends all the readed data inot log file
    string line;                         //without erasing the old data
    if(!file.is_open()){
        cout<<"Unable to open request.txt"<<endl;
        return 1;
    } 
    map <string, int> ipcount;  
    map <string, bool> blockedCount;
    while(getline(file, line)){
        stringstream ss(line);           //stringstream extracts first string of line and names it as "line";
        
        string ip;
        ss >> ip;

        string request;
        
        getline(ss, request);
        if(blockedCount.find(ip) == blockedCount.end()){
            blockedCount[ip] = true;
        }
        if(isSQL_Inject(request) || isXSS(request)){

            ipcount[ip]++;

            cout<<"IP: "<<ip<<endl;
            log<<"IP: "<<ip<<endl;
            cout<<"Request == ( "<< request <<" ) \n";
            log<<"Request == ( "<< request << " ) " << endl;
            cout<<"Status: Blocked"<<endl;
            log<<"Status: Blocked"<<endl;
            cout<<"Times attacked: "<<ipcount[ip]<<endl;
            log<<"Times attacked: "<<ipcount[ip]<<endl;
            cout<<"-------------------------------------------\n";
            log<<"-------------------------------------------\n";
            if(ipcount[ip] >= 3){
                cout<<"Blocked: "<<ip<<" attacked more than 3 times ("<<ipcount[ip]<<" times)"<<endl;
                log<<"Blocked: "<<ip<<" attacked more than 3 times ("<<ipcount[ip]<<" times)"<<endl;
                cout<<"-------------------------------------------\n";
                log<<"-------------------------------------------\n";
                continue;
            }
        }
        else{
            cout<<"IP: "<<ip<<endl;
            log<<"IP: "<<ip<<endl;
            cout<<"Request == ( "<< request <<" ) \n";
            log<<"Request == ( "<< request << " ) " << endl;
            cout<<"Status: Safe"<<endl;
            log<<"Status: Safe"<<endl;
            cout<<"-------------------------------------------\n";
            log<<"-------------------------------------------\n";
        }
    }
        
    cout<<"\n--------------Attack Summary----------------\n";

    for(auto x: ipcount){
        if(ipcount[x.first] < 3){
            cout<<x.first<<" == "<<x.second<<" times"<<endl;
            log<<x.first<<" == "<<x.second<<" times"<<endl;
        }
        else{
            cout<<x.first<<" == "<<x.second<<" times -- WARNING"<<endl;
            log<<x.first<<" == "<<x.second<<" times -- WARNING"<<endl;
        }
    }
    return 0;
}

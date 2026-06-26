#include<iostream>
#include<string>
#include<fstream>
#include<sstream>

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
    while(getline(file, line)){
        stringstream ss(line);
        
        string ip;
        ss >> ip;

        string request;
        getline(ss, request);
        if(isSQL_Inject(request) || isXSS(request)){
            cout<<"IP: "<<ip<<endl;                                  //cout used for terminal output
            log<<"IP: "<<ip<<endl;                                  //log file used for log file output
            cout<<"Request == ( "<< request <<" ) \n";
            log<<"Request == ( "<< request << " ) " << endl;
            cout<<"Status: Blocked"<<endl;
            log<<"Status: Blocked"<<endl;
            cout<<"-------------------------------------------\n";
            log<<"-------------------------------------------\n";
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
    return 0;
}

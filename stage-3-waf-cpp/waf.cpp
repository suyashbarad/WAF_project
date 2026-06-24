#include<iostream>
#include<string>

using namespace std;
  
bool isSQL_Inject(string req){                                  //hacker tries for SQL injection that is bypass login
    if(req.find("OR 1=1") != string::npos) return true;
    if(req.find("'--") != string::npos) return true;
    return false;
}
bool isXSS(string req){                                  //hacker tries for XSS injection that is running JS into code
    if(req.find("<script>") != string::npos) return true;
    return false;
}
int main(){
    string request;
    cout<<"Enter request string: ";
    getline(cin, request);

    if(isSQL_Inject(request) || isXSS(request)){
        cout<<"Blocked! ";
    }
    else{
        cout<<"Safe! ";
    }
    return 0;
}

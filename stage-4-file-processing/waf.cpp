#include<iostream>
#include<string>
#include<fstream>

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
    ifstream file("request.txt");
    string line;
    while(getline(file, line)){
        if(isSQL_Inject(line) || isXSS(line)){
            cout<<"Blocked! == ( "<<line<<" ) \n";
        }
        else{
            cout<<"Safe! == ( "<<line<<" ) \n";
        }
    }
    return 0;
}

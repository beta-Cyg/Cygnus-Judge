#include<iostream>
#include<string>
#include<cstdlib>
#include"script/addp_sh"
using namespace std;

int main(int argc,char** Args){
	string args[argc];
	for(int i=0;i<argc;i++)
		args[i]=Args[i];
	switch(argc){
	case 1:
		cout<<"cygnus judge v0.1\n"
			<<"GNU GPLv3.0\n"
			<<"by beta-Cyg\n";
		break;
	case 2:
		if(args[1]=="version" or args[1]=="--version" or args[1]=="-v"){
			cout<<"cygnus judge v0.1\n"
				<<"GNU GPLv3.0\n"
				<<"by beta-Cyg";
		}
		else if(args[1]=="setting")
            system("visudo ~/.judgerc");
        else if(args[1]=="init")
                system("mkdir -p ~/.judge");
        else{
            cout<<"undefined option/option's syntax error\n";
            return -1;
        }
		break;
	case 3:
		if(args[1]=="addp"){
			int result=system(addp_sh(args[2]).c_str());
            if(result!=0) {
                cerr<<"unzip error!\n";
                return -1;
            }
		}
	default:
		break;
	}

	return 0;
}

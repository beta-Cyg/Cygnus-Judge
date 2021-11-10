#include<iostream>
#include<string>
#include<cstdlib>
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
		else if(args[1]=="setting"){
			system("visudo ~/.judgerc");
		}
		else{
			cout<<"undefined option/option's syntax error\n";
		}
		break;
	case 3:
		if(args[1]=="addp"){
			system(addp_sh.c_str());
		}
	default:
		break;
	}

	return 0;
}

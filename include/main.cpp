#include<iostream>
#include<string>
#include<cstdlib>
#include"script/addp_sh"
#include"script/addc_sh"
#include"project_info.h"
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
            int result=system("visudo " USER"/.judgerc");
            if(result!=0){
                return result;
            }
        }
        else if(args[1]=="init"){
            int result=system("mkdir -p " USER"/.judge");
            if(result!=0){
                return result;
            }
            result=system("mkdir -p " USER"/.judge/problem");
            if(result!=0){
                return result;
            }
            result=system("mkdir -p " USER"/.judge/message");
            if(result!=0){
                return result;
            }
            result=system("mkdir -p " USER"/.judge/competition");
            if(result!=0){
                return result;
            }
            result=system("mkdir -p " USER"/.judge/program");
            if(result!=0){
                return result;
            }
        }
        else{
            cout<<"undefined option/option's syntax error\n";
            return -1;
        }
    case 3:
        if(args[1]=="judge"){
            //solve judge
        }
	case 4:
		if(args[1]=="add"){
            if(args[2]=="problem"){
                int result=system(cyg::addp_sh(args[3]).c_str());
                if(result!=0){
                    cerr<<"unzip error!\n";
                    return result;
                }
            }
            if(args[2]=="competition"){
                int result=system(cyg::addc_sh(args[3]).c_str());
                if(result!=0){
                    cerr<<"add competition error!\n";
                    return result;
                }
            }
		}
	default:
		break;
	}

	return 0;
}

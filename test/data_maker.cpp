#include<fstream>
#include<string>
#include<cstdlib>
#include<ctime>
using namespace std;

int main(int argc,char** args){
	string arg=args[1];
	fstream fin((arg+".in").c_str(),ios::out),fout((arg+".out").c_str(),ios::out);
	srand(time(nullptr));
	int A=rand()%int(1e8),B=rand()%int(1e8);
	fin<<A<<' '<<B<<endl;
	fout<<A+B<<endl;

	return 0;
}

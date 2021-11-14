#include"xml_parser.hpp"
#include<iostream>
using namespace std;

int main(){
    cyg::problem pt("/home/beta-cyg/Cygnus-Judge/test/problem.xml");
    cout<<pt.pname<<endl;

    return 0;
}
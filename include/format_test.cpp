#include<iostream>
#include"format.hpp"
using namespace std;

int main(){
    cout<<cyg::format("{P1} is old than {P2}.",make_pair(string("P1"),string("Alan")),make_pair(string("P2"),string("Tom")))<<endl;

    return 0;
}
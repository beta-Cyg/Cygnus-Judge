#include"xml_parser.hpp"
#include<iostream>
using namespace std;

int main(){
    cyg::problem pt("/home/beta-cyg/Cygnus-Judge/test/problem.xml");
    cout<<pt.pname<<' '<<pt.time_limit<<' '<<pt.memory_limit<<endl;
    cout<<pt.subtask_n<<endl;
    for(int i=0;i<pt.subtask_n;i++){
        cout<<i+1<<":"<<endl;
        cout<<"    "<<pt.Subtask[i].point<<endl;
        for(auto iter:pt.Subtask[i].score)
            cout<<"        "<<iter<<endl;
    }

    return 0;
}
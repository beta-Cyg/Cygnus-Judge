#include<queue>
#include<iostream>
#include<thread>
#include<ctime>
#include<unistd.h>
using namespace std;

queue<thread>thread_que;

int main(){
    auto a=[](){cout<<"test"<<endl;};
    while(true){
        cout<<thread_que.size()<<endl;
        if(clock()%7==0)thread_que.emplace(a);
        while(not thread_que.empty())
            thread_que.front().detach(),
            thread_que.pop();
        sleep(1);
    }

    return 0;
}
#include<ctime>
#include<cstdio>
#include<thread>
#include<queue>
#include<utility>
#include<iostream>
#include<unistd.h>
#include"xml_parser.hpp"
#include"project_info.h"
using namespace std;

uint64_t max_thread,thread_n(0);

class judge_unit{
public:
    cyg::problem problem;
    string code;

    explicit judge_unit(const cyg::problem& p=cyg::problem(),string c=""):problem(p),code(std::move(c)){}
};

bool operator<(const judge_unit& j1,const judge_unit& j2){
    size_t p1_time_sum=0,p2_time_sum=0;
    for(size_t i=0;i<j1.problem.subtask_n;i++)
        p1_time_sum+=j1.problem.Subtask[i].point*j1.problem.time_limit;
    for(size_t i=0;i<j2.problem.subtask_n;i++)
        p2_time_sum+=j2.problem.Subtask[i].point*j2.problem.time_limit;
    return p1_time_sum<p2_time_sum;
}

priority_queue<judge_unit>judge_que;

void delay(int time/*ms*/){
    clock_t now=clock();
    while(clock()-now<time);
}

int16_t compile(const string& xml_file_name){
    return 0;//return compile result
}

int16_t judge(const judge_unit& judgeUnit){
    FILE* judge_program_input=popen("","w");
    FILE* judge_program_output=popen("","r");
    if(judge_program_input==nullptr or judge_program_output==nullptr){
        thread_n--;
        return -1;
    }
    pclose(judge_program_input);
    pclose(judge_program_output);
    thread_n--;
    return 0;
}

bool get_running_type(){
    bool result=true;
    return result;//solve it
}

void get_new_judge(){
    FILE* judge_que_file=fopen(USER"/.judge/judge_que_file","r");
    if(judge_que_file==nullptr){
        cout<<"open judge_que_file failed"<<endl;
        return;
    }
    char code_name[128],problem_name[128];
    while(fscanf(judge_que_file,"%s %s",problem_name,code_name)!=EOF){
        judge_que.emplace(cyg::problem(USER"/.judge/problem/"+string(problem_name)+"/problem.xml"),code_name);
    }
    fclose(judge_que_file);
}

int main(){
    max_thread=thread::hardware_concurrency()-1;
    while(true){
#ifdef CYG_DEBUG
        cout<<max_thread<<' '<<judge_que.size()<<endl;
#endif
        if(get_running_type()==false){
            break;
        }
        get_new_judge();
        if(judge_que.empty())continue;
        for(uint64_t i=0;i<max_thread-thread_n;i++){
            thread new_judge_thread(judge,judge_que.top());
            judge_que.pop();
            new_judge_thread.join();
        }
        sleep(1);
    }

    return 0;
}
#include<ctime>
#include<cstdio>
#include<thread>
#include<queue>
#include<utility>
#include<atomic>
#include<iostream>
#include<unistd.h>
#include"xml_parser.hpp"
#include"project_info.h"
using namespace std;

atomic<uint64_t>max_thread,thread_n(0);

class judge_unit{
public:
    cyg::problem problem;
    string code;
    string xml_file_name;

    explicit judge_unit(cyg::problem p=cyg::problem(),string c="",string xfn=""):problem(std::move(p)),code(std::move(c)),xml_file_name(std::move(xfn)){}
};

bool operator<(const judge_unit& j1,const judge_unit& j2){
    size_t p1_time_sum=0,p2_time_sum=0;
    for(auto& i:j1.problem.Subtask)
        p1_time_sum+=i.point*j1.problem.time_limit;
    for(auto& i:j2.problem.Subtask)
        p2_time_sum+=i.point*j2.problem.time_limit;
    return p1_time_sum<p2_time_sum;
}

priority_queue<judge_unit>judge_que;
queue<thread>thread_que;

inline int16_t compile_or_interpreted(const string& xml_file_name){
    boost::property_tree::ptree information_of_c_or_i;
    try{
        boost::property_tree::xml_parser::read_xml(xml_file_name,information_of_c_or_i);
    }
    catch(...){
        return -1;
    }
    bool flag=information_of_c_or_i.get<string>("run.type")=="compiled";
    if(flag){

    }//solve it
    else{

    }
    return 0;//return compile result
}

/*
 * the error code of function judge
 * 0  --- Accept (AC)
 * 1  --- Compile error (CE)
 * -1 --- Open pipe error (UE,unknown error)
 * 2  --- Wrong answer (WA)
 * 3  --- Partially correct (PC)
 * 4  --- Time limit exceeded (TLE)
 * 5  --- Memory limit exceeded (MLE)
 * */

int16_t judge(const judge_unit& judgeUnit){
    if(compile_or_interpreted(judgeUnit.xml_file_name)){
        thread_n--;
        return 1;
    }
    FILE* judge_program_input=popen(USER"/.judge/program/","w");
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
    FILE* running_type_file=fopen(USER"/.judge/running_type","r");
    if(running_type_file==nullptr){
#if CYG_DEBUG
        cout<<"can't open running type file(read)"<<endl;
#endif
        return false;
    }
    int flag;
    fscanf(running_type_file,"%d",&flag);
    fclose(running_type_file);
    cout<<"running type:"<<flag<<endl;
    running_type_file=fopen(USER"/.judge/running_type","w");
    if(running_type_file==nullptr){
#if CYG_DEBUG
        cout<<"can't open running type file(write)"<<endl;
#endif
        return false;
    }
    fprintf(running_type_file,"%d\n",flag);
    fclose(running_type_file);
    return flag;
}

void get_new_judge(){
    FILE* judge_que_file=fopen(USER"/.judge/judge_que_file","r");
    if(judge_que_file==nullptr){
#ifdef CYG_DEBUG
        cout<<"open judge_que_file failed"<<endl;
#endif
        return;
    }
    char code_name[128],problem_name[128];
    while(fscanf(judge_que_file,"%s %s",problem_name,code_name)!=EOF){
        judge_que.emplace(cyg::problem(USER"/.judge/problem/"+string(problem_name)+"/problem.xml"),code_name);
        thread_que.emplace(judge,judge_que.top());
        judge_que.pop();
    }
    fclose(judge_que_file);
    judge_que_file=fopen(USER"/.judge/judge_que_file","w");
    if(judge_que_file==nullptr){
#if CYG_DEBUG
        cout<<"open judge_que_file failed(clear the file)"<<endl;
#endif
    }
    fprintf(judge_que_file,"%s","");
}

int main(){
    max_thread=thread::hardware_concurrency()-1;
    while(true){
#ifdef CYG_DEBUG
        cout<<max_thread<<' '<<judge_que.size()<<endl;
#endif
        if(!get_running_type()){
            while(thread_n!=0);
            break;
        }
        get_new_judge();
        if(judge_que.empty()){
            sleep(1);
            continue;
        }
        for(uint64_t i=0;i<max_thread-thread_n;i++){
            thread_que.front().detach();
            thread_que.pop();
        }
        sleep(1);
    }

    return 0;
}

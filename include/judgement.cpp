#include<iostream>
#include<cstdio>
#include"format.hpp"
#include"xml_parser.hpp"
#include"project_info.h"
using namespace std;

constexpr int AC=0,PAC=1,WA=2,TLE=3,MLE=4,RE=5;

class judge_task{
public:
    cyg::problem problem;
    string src;
    string xml_file_name;

    explicit judge_task(cyg::problem p=cyg::problem(),string c="",string xfn=""):problem(std::move(p)),src(std::move(c)),xml_file_name(std::move(xfn)){}
}task;

class judge_result{
public:
    class subtask{
    public:
        class test_point{
        public:
            int64_t pts;
            int type;
            explicit test_point(const int64_t& _pts=0):pts(_pts),type(0){}
        };
        size_t point;
        std::list<test_point>score;
        explicit subtask(size_t _point=0):point(_point),score(){}

        explicit subtask(const cyg::problem::subtask& _subtask){
            point=_subtask.point;
            for(auto i:_subtask.score){
                score.emplace_back(i);
            }
        }
    };
    std::list<subtask>Subtask;
    size_t subtask_n,total_pts;

    judge_result():subtask_n(0),total_pts(0){}
};

int compile(const string& xml_file_name,const string& src){
    cyg::compile_information compile_information;
    try{
        compile_information=cyg::compile_information(xml_file_name);
    }
    catch(...){
        cerr<<"language xml file syntax error!"<<endl;
        return -1;
    }
    bool flag=compile_information.type=="compiled";
    if(flag){
        string compile_statement=cyg::format(compile_information.compiler+" "+compile_information.fmt,
                                             make_pair(string("src"),src),
                                             make_pair(string("exe"),src+(CYG_ARCH=="linux"?string(".o"):(CYG_ARCH=="windows")?string(".exe"):string())));
#ifdef CYG_DEBUG
        cout<<compile_statement<<endl;
#endif
        int result=system(compile_statement.c_str());
        if(result!=0){
            cerr<<"compile failed!\n";
            return result;
        }
    }
    //if type of programming language is interpreted then not to compile
    return 0;
}

judge_result run(const judge_task& judgeTask){//use time to get info
    judge_result result;
    result.subtask_n=judgeTask.problem.subtask_n;
    for(const auto& i:judgeTask.problem.Subtask)
        result.Subtask.emplace_back(i);
#ifdef CYG_DEBUG
    cout<<"the judgement has been to run."<<endl;
#endif
    /*for(auto& i:result.Subtask)
        for(auto& j:i.score){
            j.pts=0;*/
            string output_file_name=judgeTask.src+(
                    CYG_ARCH=="linux"?string(".o"):(CYG_ARCH=="windows")?string(".exe"):string()
                );
            string running_statement="/usr/bin/time -v "+output_file_name;// /usr/bin/time -v {exe}>{out}
            FILE* pipe=popen(running_statement.c_str(),"r");
#ifdef CYG_DEBUG
            char str[1000];
            fprintf(pipe,"%s",str);
            cout<<"str="<<str<<endl;
#endif
            pclose(pipe);
        //}
    return result;//solve this function
}

ostream& operator<<(ostream& out,const judge_result& judgeResult){
    return out;
}//solve this function

/*
 * running result code:
 * 0: AC
 * 1: PAC
 * 2: WA
 * 3: TLE
 * 4: MLE
 * 5: RE
 * */

constexpr char* result_code[6]{"AC","PAC","WA","TLE","MLE","RE"};

int main(int argc,char **args){
    if(argc!=4)return 1;
    string problem_name=args[1],code_name=args[2],xml_file_name=args[3];
    task=judge_task(cyg::problem(USER"/.judge/problem/"+string(problem_name)+"/problem.xml"),code_name,xml_file_name);
    int compile_result=compile(task.xml_file_name,task.src);
    if(compile_result!=0){
        cout<<"judge result: CE"<<endl;
        return 0;
    }
    judge_result running_result=run(task);
    cout<<running_result<<endl;

    return 0;
}
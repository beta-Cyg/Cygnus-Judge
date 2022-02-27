#include<fstream>
#include<iostream>
#include"format.hpp"
#include"xml_parser.hpp"
#include"project_info.h"
using namespace std;

class judge_task{
public:
    cyg::problem problem;
    string src;
    string xml_file_name;

    explicit judge_task(cyg::problem p=cyg::problem(),string c="",string xfn=""):problem(std::move(p)),src(std::move(c)),xml_file_name(std::move(xfn)){}
}task;

int compile(const string& xml_file_name,const string& src){
    boost::property_tree::ptree compile_information;
    try{
        boost::property_tree::xml_parser::read_xml(xml_file_name,compile_information);
    }
    catch(...){
        cerr<<"language xml file syntax error!"<<endl;
        return 1;
    }
    bool flag=compile_information.get<string>("run.type")=="compiled";
    if(flag){
        string compile_statement=cyg::format(compile_information.get<string>("run.compiler")+" "+compile_information.get<string>("run.format"),
                                             make_pair(string("src"),src),
                                             make_pair(string("exe"),src+(CYG_ARCH=="linux"?string(".o"):(CYG_ARCH=="windows")?string(".exe"):string())));
#ifdef CYG_DEBUG
        cout<<compile_statement<<endl;
#endif
        int result=system(compile_statement.c_str());
        if(result!=0){
            cerr<<"add competition error!\n";
            return result;
        }
    }
    //if type of programming language is interpreted then not to compile
    return 0;
}

int main(int argc,char **args){
    if(argc!=4)return 1;
    string problem_name=args[1],code_name=args[2],xml_file_name=args[3];
    task=judge_task(cyg::problem(USER"/.judge/problem/"+string(problem_name)+"/problem.xml"),code_name,xml_file_name);
    compile(task.xml_file_name,task.src);

    return 0;
}
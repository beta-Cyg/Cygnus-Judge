#ifndef XML_PARSER_HPP
#define XML_PARSER_HPP

#include<boost/property_tree/ptree.hpp>
#include<utility>
#include<boost/property_tree/xml_parser.hpp>
#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<string>
#include<list>
#include"unit.hpp"

namespace cyg{
    class problem_exception:public std::exception{
    public:
        std::string reason;
        explicit problem_exception(std::string _reason=""):reason(std::move(_reason)){}
        const char* what(){
            return reason.c_str();
        }
    };
	class problem{
    public:
	    std::string pname;
        int memory_limit,time_limit;
        class subtask{
        public:
            std::size_t point;
            std::list<long long>score;
            explicit subtask(std::size_t _point=0):point(_point),score(){}
            ~subtask(){score.clear();}
        };
        subtask* Subtask;
        int subtask_n;
        problem(const std::string& xml_file_name){
            boost::property_tree::ptree xml_ptree;
            try{
                boost::property_tree::read_xml(xml_file_name,xml_ptree);
            }
            catch(std::exception& _exception){
                throw problem_exception("syntax of the xml document is wrong.");
            }
            pname=xml_ptree.get<std::string>("problem.name");
            std::string ml=xml_ptree.get<std::string>("problem.memory_limit");
            std::string tl=xml_ptree.get<std::string>("problem.time_limit");
            char ml_unit=ml.back();
            char tl_unit=tl.back();
            ml.pop_back();
            tl.pop_back();
            int mlt=atoi(ml.c_str());
            int tlt=atoi(tl.c_str());
            /*
            memory_limit=cyg::convert<cyg::>();
            *///solve the unit convert
            memory_limit=mlt;
            time_limit=tlt;
            subtask_n=xml_ptree.get<int>("problem.subtask");
            Subtask=new subtask[subtask_n];
            for(int i=0;i<subtask_n;i++){
                Subtask[i].point=xml_ptree.get<int>("problem.subtask"+std::to_string(i+1)+".point");//problem.subtask$n.point
                for(int j=0;j<Subtask[i].point;j++){
                    Subtask[i].score.push_back(xml_ptree.get<int>("problem.subtask"+std::to_string(i+1)+".point"+std::to_string(j+1)));
                }
            }
        }

        ~problem(){
            delete[] Subtask;
        }
	};
}

#endif
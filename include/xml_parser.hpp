#ifndef XML_PARSER_HPP
#define XML_PARSER_HPP

#include<boost/property_tree/ptree.hpp>
#include<utility>
#include<boost/property_tree/xml_parser.hpp>
#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<string>

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
        class subtask{
        public:
            std::size_t point;
            long long* score;
            subtask(std::size_t _point):point(_point),score(new long long[point]){}
        };
        subtask* Subtask;
        problem(std::string xml_file_name){
            boost::property_tree::ptree xml_ptree;
            try{
                boost::property_tree::read_xml(xml_file_name,xml_ptree);
            }
            catch(std::exception& _exception){
                std::cerr<<_exception.what()<<std::endl;
            }
            pname=xml_ptree.get<std::string>("problem.name");
        }
	};
}

#endif
CXX=g++-11
CC=gcc-11
debug=-Wall
optimize=-O2
add_include_path=-Iinclude

all: main judgement

main: include/main.cpp
	$(CXX) include/main.cpp -o bin/judge $(debug) $(add_include_path) $(optimize)

judgement: include/judgement.cpp xmlp
	$(CXX) include/judgement.cpp -o bin/judgement $(debug) $(optimize)

judge_server: include/cjudge_server.cpp xmlp
	$(CXX) include/cjudge_server.cpp -o bin/cjudge_server $(debug) -lpthread

xmlp: include/xml_parser.hpp

xmlpt: include/xmlp_test.cpp xmlp
	$(CXX) include/xmlp_test.cpp -o bin/xmlpt $(debug)

unitt: include/unit.hpp include/unit_test.cpp
	$(CXX) include/unit_test.cpp -o bin/unitt $(debug)

formatt: include/format.hpp include/format_test.cpp
	$(CXX) include/format_test.cpp -o bin/formatt $(debug)

thread_quet: include/thread_que_test.cpp
	$(CXX) include/thread_que_test.cpp -o bin/thread_quet $(debug) -lpthread

jsc: include/judge_server_control.cpp
	$(CXX) include/judge_server_control.cpp -o bin/jsc $(debug)

init:
	mkdir -p bin lib

clean:
	rm -rf bin lib

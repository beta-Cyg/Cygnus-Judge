CXX=clang++-12
CC=clang-12
debug=-Wall
optimize=-O2
add_include_path=-Iinclude

all: formatt main jsc judge_server thread_quet

main: include/main.cpp judge_server
	$(CXX) include/main.cpp -o bin/judge $(debug) $(add_include_path)

judge_server: include/cjudge_server.cpp xmlp
	$(CXX) include/cjudge_server.cpp -o bin/cjudge_server $(debug) -lpthread

xmlp: include/xml_parser.hpp

xmlpt: include/xmlp_test.cpp xmlp
	$(CXX) include/xmlp_test.cpp -o bin/xmlpt $(debug)

unitt: include/unit.hpp include/unit_test.cpp
	$(CXX) include/unit_test.cpp -o bin/unitt $(debug)

formatt: include/format.hpp include/format_test.cpp
	$(CXX) include/format_test.cpp -o bin/formatt $(debug) -std=c++20

thread_quet: include/thread_que_test.cpp
	$(CXX) include/thread_que_test.cpp -o bin/thread_quet $(debug) -lpthread

jsc: include/judge_server_control.cpp
	$(CXX) include/judge_server_control.cpp -o bin/jsc $(debug)

init:
	mkdir -p bin lib

clean:
	rm -rf bin lib

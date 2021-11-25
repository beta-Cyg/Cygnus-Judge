CXX=g++-11
CC=gcc-11
debug=-Wall
optimize=-O2
add_include_path=-Iinclude

all: clean init main judge_server

main: include/main.cpp judge_server init
	$(CXX) include/main.cpp -o bin/judge $(debug) $(add_include_path)

judge_server: include/cjudge_server.cpp xmlp init
	$(CXX) include/cjudge_server.cpp -o bin/cjudge_server $(debug) -lpthread

xmlp: include/xml_parser.hpp init

xmlpt: include/xmlp_test.cpp xmlp init
	$(CXX) include/xmlp_test.cpp -o bin/xmlpt $(debug)

unitt: include/unit.hpp include/unit_test.cpp init
	$(CXX) include/unit_test.cpp -o bin/unitt $(debug)

init: clean
	mkdir -p bin lib

clean:
	rm -rf bin lib

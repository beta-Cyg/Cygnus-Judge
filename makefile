CXX=g++-11
C=gcc-11
debug=-Wall

all: clean init main

main: include/main.cpp judge_server
	$(CXX) include/main.cpp -o bin/judge -O2 $(debug)

judge_server: include/judge_server.cpp xmlp
	$(CXX) include/judge_server.cpp -o bin/judge_server -O2 $(debug)

xmlp: include/xml_parser.hpp

xmlpt: include/xmlp_test.cpp xmlp
	$(CXX) include/xmlp_test.cpp -o bin/xmlpt -O2 $(debug)

unitt: include/unit.hpp include/unit_test.cpp
	$(CXX) include/unit_test.cpp -o bin/unitt -O2 $(debug)

init:
	mkdir -p bin lib

clean:
	rm -rf bin lib

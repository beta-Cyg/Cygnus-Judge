CXX=g++
C=gcc
debug=-Wall

all: init main xmlpt unitt

main: include/main.cpp xmlp
	$(CXX) include/main.cpp -o bin/judge -O2 $(debug)

xmlp: include/xml_parser.hpp
	$(CXX) -c include/xml_parser.hpp -o lib/xmlp.o -O2 $(debug)
	ar rcs lib/xmlp.a lib/xmlp.o
	rm lib/xmlp.o

xmlpt: include/xmlp_test.cpp xmlp
	$(CXX) include/xmlp_test.cpp -o bin/xmlpt -O2 $(debug)

unitt: include/unit.hpp include/unit_test.cpp
	$(CXX) include/unit_test.cpp -o bin/unitt -O2 $(debug)

init:
	mkdir -p bin lib

clean:
	rm -rf bin lib

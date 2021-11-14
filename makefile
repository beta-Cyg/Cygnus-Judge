CC=g++
C=gcc
debug=-Wall

all: init main xmlpt

main: include/main.cpp xmlp
	$(CC) include/main.cpp -o bin/judge -O2 $(debug)

xmlp: include/xml_parser.hpp
	$(CC) -c include/xml_parser.hpp -o lib/xmlp.o -O2 $(debug)
	ar rcs lib/xmlp.a lib/xmlp.o
	rm lib/xmlp.o

xmlpt: include/xmlp_test.cpp xmlp
	$(CC) include/xmlp_test.cpp -o bin/xmlpt -O2 $(debug)

init:
	mkdir -p bin lib

clean:
	rm -rf bin lib

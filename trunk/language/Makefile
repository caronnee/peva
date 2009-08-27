CFLAGS=-O0 -g -Wall
LDFLAGS= `xml2-config --cflags --libs`
XML=`xml2-config --cflags`

all:bparser 

bparser: bison.o help.o instructions.o memory.o node.o biflex.o parser.o bot.o types.o  tree.o variable.o functions.o targets.o
	$(CXX) $(LDFLAGS) *.o -o bparser

parser.o: parser.cpp header1.h 
	${CXX} ${CPPFLAGS} ${CFLAGS} ${XML} -o $@ -c parser.cpp

bison.o:bison.cpp
	${CXX} ${CPPFLAGS} ${XML} -o $@ -c $<

functions.o:functions.cpp functions.h
	${CXX} ${CPPFLAGS} ${CFLAGS} -o $@ -c functions.cpp

bison.hpp:bison.cpp

parser.cpp:parser.lex bison.hpp
	flex -Cf -b -p -p -o $@ $<

bison.cpp: bison.y
	bison --report=all -d -b bis -o $@ $<

bot.o:	./robot.h ./robot.cpp
	${CXX} ${CPPFLAGS} -c ${XML} -o $@ ./robot.cpp

biflex.o:parser_functions.h parser_functions.cpp
	${CXX} ${CFLAGS} ${XML} -o $@ -c parser_functions.cpp

tree.o:./tree.cpp ./tree.h
	${CXX} ${CFLAGS} -o $@ -c ./tree.cpp

node.o:./node.cpp ./node.h
	${CXX} ${CFLAGS} -o $@ -c ./node.cpp

instructions.o: instructions.h instructions.cpp
	${CXX} ${CFLAGS} -c ${XML} -o $@ instructions.cpp

variable.o:variable.h variable.cpp
	${CXX} ${CFLAGS} -c -o $@ variable.cpp

help.o:	help_functions.h help_functions.cpp
	${CXX} ${CFLAGS} -c -o $@ help_functions.cpp

memory.o: memory.h memory.cpp 
	${CXX} ${CFLAGS} -c -o $@ memory.cpp

types.o: types.h types.cpp
	${CXX} ${CFLAGS} -c -o $@ types.cpp

targets.o: targets.cpp targets.h
	${CXX} ${CFLAGS} -c -o $@ targets.cpp

distclean:
	rm -f *.o bparser parser.cpp bison.cpp bison.hpp

run:
	make
	./bparser vstup

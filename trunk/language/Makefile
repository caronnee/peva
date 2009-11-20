CFLAGS=-O0 -g -Wall
LDFLAGS= `xml2-config --cflags --libs`
XML=`xml2-config --cflags`

all:bparser 

bparser: bison.o help.o instructions.o memory.o node.o biflex.o parser.o bot.o types.o  tree.o variable.o functions.o targets.o core.o position.o parser_classes.o typeContainer.o
	$(CXX) $(LDFLAGS) *.o -o bparser

typeContainer.o: typeContainer.h typeContainer.cpp
	${CXX} ${CPPFLAGS} ${XML} ${CFLAGS} -o $@ -c typeContainer.cpp

parser_classes.o: parser_classes.h parser_classes.cpp
	${CXX} ${CPPFLAGS} ${XML} ${CFLAGS} -o $@ -c parser_classes.cpp

parser.o: parser.cpp lval.h 
	${CXX} ${CPPFLAGS} ${CFLAGS} ${XML} -o $@ -c parser.cpp

bison.o:bison.cpp hflex.h
	${CXX} ${CPPFLAGS} ${XML} -o $@ -c $<

functions.o:functions.cpp functions.h
	${CXX} ${CPPFLAGS} ${CFLAGS} -o $@ -c functions.cpp

bison.hpp:bison.cpp

hflex.h:parser.cpp

parser.cpp:parser.lex
	flex -Cf -b -p -p --header-file=hflex.h -o $@ $<

bison.cpp: bison.y
	bison --report=all -d -b bis -o $@ $<

bot.o:	robot.h robot.cpp
	${CXX} ${CPPFLAGS} -c ${XML} -o $@ robot.cpp

biflex.o:parser_functions.h parser_functions.cpp
	${CXX} ${CFLAGS} ${XML} -o $@ -c parser_functions.cpp

tree.o: tree.cpp tree.h
	${CXX} ${CFLAGS} -o $@ -c ./tree.cpp

node.o: node.cpp node.h
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

core.o: core.h core.cpp
	${CXX} ${CFLAGS} -c -o $@ core.cpp

position.o: position.h position.cpp
	${CXX} ${CFLAGS} -c -o $@ position.cpp

distclean:
	rm -f *.o bparser hflex.h parser.cpp bison.cpp bison.hpp

run:
	make
	./bparser vstup
rerun:
	make distclean
	make
	./bparser vstup

debugMemory:
	make
	valgrind -v --tool=memcheck --leak-check=yes --show-reachable=yes --track-origins=yes --num-callers=20 --track-fds=yes ./bparser vstup

debugGraph:
	make
	valgrind --tool=cachegrind ./bparser vstup

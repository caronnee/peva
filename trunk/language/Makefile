CFLAGS=-O0 -g -Wall
LDFLAGS= `xml2-config --cflags --libs`
XML=`xml2-config --cflags`

all:bparser 

bparser:parser.o bison.o bot.o biflex.o tree.o instructions.o node.o
	$(CXX) $(LDFLAGS) *.o -o bparser

parser.o: parser.cpp header1.h tokens.h
	${CXX} ${CPPFLAGS} ${CFLAGS} ${XML} -o $@ -c parser.cpp

bison.o:bison.cpp
	${CXX} ${CPPFLAGS} ${XML} -o $@ -c $<

bison.hpp:bison.cpp

parser.cpp:parser.lex bison.hpp
	flex -Cf -b -p -p -o $@ $<

bison.cpp: bison.y
	bison --report=all -d -b bis -o $@ $<

bot.o:	./tree/my_stack.h ./tree/my_stack.cpp
	${CXX} ${CPPFLAGS} -c ${XML} -o $@ ./tree/my_stack.cpp

biflex.o:parser_functions.h parser_functions.cpp
	${CXX} ${CFLAGS} ${XML} -o $@ -c parser_functions.cpp

tree.o:./tree/tree.cpp ./tree/tree.h
	${CXX} ${CFLAGS} -o $@ -c ./tree/tree.cpp

node.o:./tree/node.cpp ./tree/node.h
	${CXX} ${CFLAGS} -o $@ -c ./tree/node.cpp

instructions.o: instructions.h instructions.cpp
	${CXX} ${CFLAGS} -c ${XML} -o $@ instructions.cpp

distclean:
	rm -f *.o bparser parser.cpp bison.cpp bison.hpp

run:
	./bparser vstup

CFLAGS=-O0 -g -Wall
LDFLAGS= `xml2-config --cflags --libs`
XML=`xml2-config --cflags`
HEADER_DIR=h/
OBJECT_DIR=../objects/
SRC=cpp/

.PHONY:bparse distclean debugMemory debugGraph

all:bparser dep

bparser: bison.o help.o instructions.o memory.o node.o biflex.o \
	parser.o bot.o types.o  tree.o variable.o functions.o \
	targets.o core.o position.o parser_classes.o typeContainer.o \
	language.o
	$(CXX) $(LDFLAGS) *.o -o ../bparser

bison.hpp:bison.cpp

hflex.h:parser.cpp

parser.cpp:parser.lex
	flex -Cf -b -p -p --header-file=$(HEADER_DIR)hflex.h -o $@ $<

bison.cpp: bison.y hflex.h
	bison --report=all -d -b bis --defines=$(HEADER_DIR)bison.h -o $(SRC)$@ $<

%.o: cpp/%.cpp
	@echo "Compiling "
	@echo $@
	${CXX} ${CFLAGS} -c ${XML} -o $@ $*.cpp

distclean:
	rm -f $(OBJECT_DIR)*.o bparser $(HEADER_DIR)hflex.h parser.cpp $(SRC)bison.cpp bison.hpp

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

dep:
	touch Makefile.dep
	makedepend -Y -f Makefile.dep *.cpp 2> /dev/null
	rm -f Makefile.dep.bak

-include Makefile.dep

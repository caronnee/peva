CFLAGS=-O0 -g -Wall
LDFLAGS=`sdl-config --cflags --libs` -lSDL_ttf -lSDL_image `xml2-config --cflags --libs` -lboost_filesystem
XML=`xml2-config --cflags`
HEADER_DIR=h/
OBJECT_DIR=o/
SRC=cpp/

lOBJECTS=o/bison.o o/help_functions.o o/instructions.o o/memory.o o/node.o o/parser_functions.o \
	o/parser.o o/robot.o o/types.o o/tree.o o/variable.o o/functions.o \
	o/targets.o o/core.o o/position.o o/parser_classes.o o/typeContainer.o \
	o/body.o o/objects.o o/missille.o o/images.o o/scheduller.o o/list.o
	
gOBJECTS=o/help_functions.o o/position.o o/movement.o o/snake.o \
	o/create_map.o o/graphic.o o/main_menu.o \
	o/other.o o/map.o o/body.o o/objects.o \
	o/wall.o o/images.o
	
LANGUAGE_OBJECTS= o/language.o $(lOBJECTS)

.PHONY:bparser distclean debugMemory debugGraph debugGMemory debugGGraph test bparser codewars


all: dep bparser codewars test

test:	o/list.o o/test.o o/objects.o o/position.o o/images.o
	@echo ""
	@echo "..........................................."
	@echo "Creating test for testing list...:"
	g++ $(LDFLAGS) -o $@ $^
	@echo "..........................................."

codewars:$(lOBJECTS) $(gOBJECTS) o/main.o
	@echo "..........................................."
	@echo "Creating main project file..."
	g++ $(LDFLAGS) -o $@ $^
	@echo "..........................................."

bparser: $(LANGUAGE_OBJECTS)
	@echo "..........................................."
	@echo "Creatinf file for testing language:"
	$(CXX) $(LDFLAGS) $(LANGUAGE_OBJECTS) -o bparser
	@echo "..........................................."

language/h/bison.h:language/cpp/bison.cpp

language/h/hflex.h:language/cpp/parser.cpp

language/cpp/parser.cpp:language/parser.lex
	flex -Cf -b -p -p --header-file=language/$(HEADER_DIR)hflex.h -o $@ $<

language/cpp/bison.cpp: language/bison.y language/h/hflex.h
	bison --report=all -d -b bis --defines=language/$(HEADER_DIR)bison.h -o $@ $<

o/bison.o: language/cpp/bison.cpp 
	${CXX} ${CFLAGS} -c ${XML} -o $@ $<

o/parser.o: language/cpp/parser.cpp
	${CXX} ${CFLAGS} -c ${XML} -o $@ $<

o/language.o: language/h/bison.h

o/language.o: language/h/hflex.h

o/%.o: */cpp/%.cpp
	@echo ""
	@echo "Compiling " + $@ + " from $*...:"
	${CXX} ${CFLAGS} -c ${XML} -o $@ $<

distclean:
	rm -rf o/* bparser codewars language/$(HEADER_DIR)hflex.h language/$(SRC)parser.cpp \
	language/$(SRC)bison.cpp language/$(HEADER_DIR)bison.h test

brun:
	make
	./bparser vstup
run:
	make
	./codewars
rerun:
	make distclean
	make
	./codewars

debugMemory:
	make
	valgrind -v --tool=memcheck --leak-check=yes --show-reachable=yes --num-callers=20 --track-fds=yes ./bparser vstup

debugGraph:
	make
	valgrind --tool=cachegrind ./bparser vstup

debugGMemory:
	make
	valgrind -v --tool=memcheck --leak-check=yes --show-reachable=yes --num-callers=20 --track-fds=yes ./codewars

debugGGraph:
	make
	valgrind --tool=cachegrind ./codewars

dep:
	touch Makefile.dep
	@if [ ! -d o ]; then echo "Creating compile objects directory"; mkdir o; fi
	find . -name "*.cpp" |xargs  makedepend -Y -f Makefile.dep  2> /dev/null	
	rm -f Makefile.dep.bak

remake:
	make distclean
	make

-include Makefile.dep

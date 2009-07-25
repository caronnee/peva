LDFLAGS=`xml2-config --cflags --libs`
XML= `xml2-config --cflags`

all:tree

tree: tree.o stack.o my_tree.o node.o instructions.o
	g++ $(LDFLAGS) -o tree *.o

node.o: node.cpp node.h
	g++ ${CPPFLAGS} ${CFLAGS} -o node.o -c node.cpp
	
my_tree.o:my_tree.cpp
	g++ ${CPPFLAGS} ${CFLAGS} ${XML} -o my_tree.o -c my_tree.cpp

tree.o: tree.cpp tree.h
	g++ ${CPPFLAGS} ${CFLAGS} -o tree.o -c tree.cpp

stack.o:my_stack.h my_stack.cpp
	g++ ${CPPFLAGS} ${CFLAGS} ${XML} -o stack.o -c my_stack.cpp

instructions.o: ../instructions.h ../instructions.cpp
	g++ ${CPPFLAGS} ${CFLAGS} ${XML} -o instructions.o -c ../instructions.cpp

distclean:
	rm -f *.o tree

run:
	make
	./tree


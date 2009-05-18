all:tree

tree: tree.o stack.o
	g++ $(LDFLAGS) -o tree *.o

tree.o: my_tree.cpp
	g++ ${CPPFLAGS} ${CFLAGS} -o tree.o -c my_tree.cpp

stack.o:my_stack.h my_stack.cpp
	g++ ${CPPFLAGS} ${CFLAGS} -o stack.o -c my_stack.cpp

distclean:
	rm *.o tree


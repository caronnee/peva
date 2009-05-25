all:bparser 

bparser:parser.o bison.o bot.o biflex.o
	$(CXX) $(LDFLAGS) parser.o bison.o bot.o biflex.o -o bparser

parser.o: parser.cpp header1.h tokens.h
	${CXX} ${CPPFLAGS} ${CFLAGS} -o $@ -c parser.cpp

bison.o:bison.cpp
	${CXX} ${CPPFLAGS} -o $@ -c $<

bison.hpp:bison.cpp

parser.cpp:parser.lex bison.hpp
	flex -Cf -b -p -p -o $@ $<

bison.cpp: bison.y
	bison --report=all -d -b bis -o $@ $<

bot.o:	./tree/my_stack.h ./tree/my_stack.cpp
	${CXX} ${CPPFLAGS} -o $@ -c ./tree/my_stack.cpp

biflex.o:parser_functions.h parser_functions.cpp
	${CXX} ${CFLAGS} -o $@ -c parser_functions.cpp

distclean:
	rm -f *.o bparser parser.cpp bison.cpp bison.hpp

run:
	./bparser vstup

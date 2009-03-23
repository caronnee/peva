all:bparser 

bparser:parser.o bison.o
	$(CXX) $(LDFLAGS) parser.o bison.o -o bparser 

parser.o: parser.cpp header1.h tokens.h
	${CXX} ${CPPFLAGS} ${CFLAGS} -o $@ -c parser.cpp

bison.o:bison.cpp
	${CXX} ${CPPFLAGS} -o $@ -c $<

parser.cpp:parser.lex bison.hpp
	flex -Cf -b -p -p -o $@ $<

bison.cpp: bison.y
	bison --report=all -d -b bis -o $@ $<

distclean:
	rm *.o bparser parser.cpp bison.cpp

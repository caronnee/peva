all:bparser 

bparser:parser.o bison.o
	$(CXX) $(LDFLAGS) parser.o bison.o 

parser.o: parser.cpp header1.h tokens.h
	${CXX} ${CPPFLAGS} ${CFLAGS} -o $@ -c parser.cpp

bison.o:bison.cpp
	${CXX} ${CPPFLAGS} -o $@ -c $<

parser.cpp:parser.lex
	flex -Cf -b -p -p -o $@ $<

bison.cpp: bison.y
	bison --report=all -d -o $@ $<

distclean:
	rm parser.cpp parser.o

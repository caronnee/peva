all:parser 

parser:parser.cpp header1.h tokens.h
	$(CXX) parser.cpp -o parser
	
parser.cpp:parser.lex
	flex -Cf -b -p -p -o $@ $<

distclean:
	rm parser.cpp parser.o

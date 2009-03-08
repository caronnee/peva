all:countchar 

countchar:countchar.cpp count.h count2.h
	$(CXX) countchar.cpp -o countchar
	
countchar.cpp:countchar.lex
	flex -Cf -b -p -p -o $@ $<

distclean:
	rm countchar.cpp countchar.o

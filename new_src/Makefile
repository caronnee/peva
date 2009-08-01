CFLAGS=-O0 -g -Wall
LDFLAGS= `sdl-config --cflags --libs` -lSDL_ttf -lSDL_image `xml2-config --cflags --libs`

all: codewars

distclean: 
		rm -f codewars *.o codewars.config

codewars: game.o draw.o objects.o wall.o help.o create.o main_menu.o other.o position.o movement.o snake.o
		g++ $(LDFLAGS) -o codewars *.o

game.o: main.cpp
		g++ -c $(CFLAGS) -o game.o main.cpp 

draw.o: draw.h draw.cpp
		g++ -c $(CFLAGS) -o draw.o draw.cpp 

objects.o: objects.h objects.cpp
		g++ -c $(CFLAGS) -o objects.o objects.cpp

wall.o: wall.h wall.cpp
		g++ -c $(CFLAGS) -o wall.o wall.cpp

help.o:help_functions.h help_functions.cpp
		g++ -c $(CFLAGS) -o help.o help_functions.cpp

create.o:create_map.h create_map.cpp
		g++ -c `xml2-config --cflags` -o create.o create_map.cpp

main_menu.o:main_menu.h main_menu.cpp
		g++ -c $(CFLAGS) -o main_menu.o main_menu.cpp

other.o:other.h other.cpp
		g++ -c $(CFLAGS) -o other.o other.cpp

position.o: position.h position.cpp
		g++ -c $(CFLAGS) -o position.o position.cpp

movement.o: movement.h movement.cpp
		g++ -c $(CFLAGS) -o movement.o movement.cpp

snake.o: snake.h snake.cpp
	g++ -c $(CFLAGS) -o snake.o snake.cpp

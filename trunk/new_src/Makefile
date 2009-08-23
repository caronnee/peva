CFLAGS=-O0 -g -Wall
LDFLAGS= `sdl-config --cflags --libs` -lSDL_ttf -lSDL_image `xml2-config --cflags --libs`

.PHONY: all

all: codewars

distclean: 
		rm -f codewars *.o codewars.config

codewars: game.o graphic.o objects.o wall.o help.o create.o main_menu.o other.o position.o movement.o snake.o map.o missille.o
		g++ $(LDFLAGS) -o codewars *.o

game.o: main.cpp
		g++ -c $(CFLAGS) -o game.o main.cpp 

graphic.o: graphic.h graphic.cpp
		g++ -c $(CFLAGS) -o graphic.o graphic.cpp 

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
map.o: map.cpp map.h
	g++ -c $(CFLAGS) -o map.o map.cpp
missille.o: missille.h missille.cpp map.h
	g++ -c $(CFLAGS) -o missille.o missille.cpp

run:
	make
	./codewars

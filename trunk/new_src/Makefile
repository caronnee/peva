CFLAGS=-O0 -g -Wall
LDFLAGS= `sdl-config --cflags --libs`  -lSDL_ttf -lSDL_image

all: codewars

distclean: 
		rm -f codewars *.o

codewars: game.o draw.o objects.o wall.o help.o create.o main_menu.o other.o
		g++ $(LDFLAGS) -o codewars game.o draw.o wall.o objects.o create.o main_menu.o other.o help.o

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
		g++ -c $(CFLAGS) -o create.o create_map.cpp

main_menu.o:main_menu.h main_menu.cpp
		g++ -c $(CFLAGS) -o main_menu.o main_menu.cpp

other.o:other.h other.cpp
		g++ -c $(CFLAGS) -o other.o other.cpp

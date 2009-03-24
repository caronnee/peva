TARGET		= codewars
CC		= g++
CFLAGS		= $(shell sdl-config --cflags)
LDFLAGS		= $(shell sdl-config --libs)

$(TARGET): main.cpp bots.cpp bots.h generuj.cpp generuj.h steny.cpp steny.h strela.cpp strela.h
	$(CC) -o $(TARGET) main.cpp bots.cpp generuj.cpp steny.cpp strela.cpp $(CFLAGS) $(LDFLAGS) -lSDL_image -lSDL_ttf

clean:
	rm -f $(TARGET) core

CC = gcc
CFLAGS = -W -Wall -ansi -std=c99 -g
LIBS = # -L./SDL2_ttf/.libs
LDFLAGS = `sdl2-config --cflags --libs` -lSDL2_ttf -lSDL2_image
INCLUDES = # -I./SDL2_ttf
EXEC = main
SRC = graphique.c monde.c main.c fonctions_SDL.c evenements.c animations.c menu.c
OBJ = $(SRC:.c=.o)

all: $(EXEC)
main: $(OBJ)
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ $^ $(LIBS) $(LDFLAGS)
%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $<
clean:
	rm -rf *.o *~
mrproper: clean
	rm -rf $(EXEC)

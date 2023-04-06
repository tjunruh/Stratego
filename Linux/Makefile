CC      =g++
CFLAGS  =-Wall -O2
#LD      =g++

all: Stratego

Stratego: Stratego.o game_operations.o
	$(CC) $(CFLAGS) -o Stratego Stratego.o game_operations.o -lncurses

Stratego.o: Stratego.cpp game_operations.h game_operations.cpp
	$(CC) $(CFLAGS) -c Stratego.cpp -lncurses

game_operations.o: game_operations.cpp
	$(CC) $(CFLAGS) -c game_operations.cpp -lncurses
#game_operations.o: game_operations.h

#%.o: %.cpp
#	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf *.o *~ Stratego


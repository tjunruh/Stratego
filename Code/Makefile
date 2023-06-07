CC      =g++
CFLAGS  =-Wall -O2

all: Stratego

Stratego: Stratego.o game_operations.o display.o logic.o file_managment.o pieces.o input_to_logic_interface.o io.o piece.o
	$(CC) $(CFLAGS) -o Stratego Stratego.o game_operations.o display.o logic.o file_managment.o pieces.o input_to_logic_interface.o io.o piece.o -lncurses

Stratego.o: Stratego.cpp game_operations.h game_operations.cpp
	$(CC) $(CFLAGS) -c Stratego.cpp -lncurses

game_operations.o: game_operations.cpp display.h display.cpp io.h io.cpp logic.h logic.cpp user_input.h input_to_logic_interface.h input_to_logic_interface.cpp file_managment.h file_managment.cpp
	$(CC) $(CFLAGS) -c game_operations.cpp

display.o: display.cpp piece.h piece.cpp io.h io.cpp direction.h
	$(CC) $(CFLAGS) -c display.cpp

logic.o: logic.cpp pieces.h pieces.cpp logic_input.h direction.h
	$(CC) $(CFLAGS) -c logic.cpp

file_managment.o: file_managment.cpp
	$(CC) $(CFLAGS) -c file_managment.cpp

pieces.o: pieces.cpp piece.h piece.cpp
	$(CC) $(CFLAGS) -c pieces.cpp

input_to_logic_interface.o: input_to_logic_interface.cpp user_input.h logic_input.h
	$(CC) $(CFLAGS) -c input_to_logic_interface.cpp

io.o: io.cpp
	$(CC) $(CFLAGS) -c io.cpp

piece.o: piece.cpp
	$(CC) $(CFLAGS) -c piece.cpp



clean:
	rm -rf *.o *~ Stratego

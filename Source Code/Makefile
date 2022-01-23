CC=g++
CFLAGS=-lstdc++fs

Catcher: Catcher.o Player.o
	clear
	$(CC) -o Catcher Catcher.o Player.o -lsfml-graphics -lsfml-window -lsfml-system -lstdc++fs

Catcher.o: Catcher.cpp Player.hpp
	clear
	$(CC) $(CFLAGS) -c Catcher.cpp

Player.o: Player.hpp

clean :
	-rm *.o $(objects)

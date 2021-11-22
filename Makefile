CC = g++
TARGET = sfml
OBJS = main.o map.o player.o key_control.o weapon.o missile.o sniper.o indicator.o game.o

$(TARGET) : $(OBJS)
	$(CC) -o $@ $^ -lsfml-graphics -lsfml-window -lsfml-system

main.o : main.cpp
	$(CC) -c $<

game.o : game.cc
	$(CC) -c $<

map.o : map.cc
	$(CC) -c $<

player.o : player.cc
	$(CC) -c $<

key_control.o : key_control.cc
	$(CC) -c $<

weapon.o : weapon.cc
	$(CC) -c $<

missile.o : missile.cc
	$(CC) -c $<

sniper.o : sniper.cc
	$(CC) -c $<

indicator.o : indicator.cc
	$(CC) -c $<

clean : 
	rm -f *.o sfml

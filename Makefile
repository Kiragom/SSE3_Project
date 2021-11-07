CC = g++
TARGET = sfml
OBJS = main.o key_control.o missile.o

$(TARGET) : $(OBJS)
	$(CC) -o $@ $^ -lsfml-graphics -lsfml-window -lsfml-system

main.o : main.cpp
	$(CC) -c $<

key_control.o : key_control.cc
	$(CC) -c $<

missile.o : missile.cc
	$(CC) -c $<

clean : 
	rm -f *.0 sfml

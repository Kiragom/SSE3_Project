CC = g++
TARGET = sfml
OBJS = main.o

$(TARGET) : $(OBJS)
	$(CC) -o $@ $^ -lsfml-graphics -lsfml-window -lsfml-system

main.o : main.cpp
	$(CC) -c $<

clean : 
	rm -f *.0 sfml

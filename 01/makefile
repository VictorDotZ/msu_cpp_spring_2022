CC=g++
FLAGS=-std=c++2a -Wall -Werror -fsanitize=address -Wextra -pedantic-errors

all: allocator

allocator: main.o Allocator.o
	$(CC) $(FLAGS) -o Allocator.out main.o Allocator.o

main.o: main.cpp Allocator.hpp
	$(CC) $(FLAGS) -c main.cpp

allocator.o: Allocator.cpp Allocator.hpp
	$(CC) $(FLAGS) -c Allocator.cpp

clean:
	rm -rf *.o
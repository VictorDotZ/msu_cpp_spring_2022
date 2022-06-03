CC=g++
FLAGS=-std=c++2a -Wall -Werror -Wunused-variable -Wsign-conversion -Wextra -fsanitize=address -pthread
TEST_FLAGS=-lgtest -lpthread 

all: main

main: main.o 
	$(CC) $(FLAGS) -o main.out main.o $(TEST_FLAGS)
	./main.out

main.o: main.cpp Queue.hpp
	$(CC) $(FLAGS) -c main.cpp

clean:
	rm -rf *.o *.out *.a
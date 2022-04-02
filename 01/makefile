CC=g++
FLAGS=-std=c++2a -Wall -Werror -Wunused-variable -Wsign-conversion -Wextra -fsanitize=address
TEST_FLAGS=-lgtest -lpthread

all: allocator test

test: TestAllocator.o Allocator.o
	$(CC) $(FLAGS) -o Test.out TestAllocator.o Allocator.o $(TEST_FLAGS)
	./Test.out

test.o: TestAllocator.cpp Allocator.hpp
	$(CC) $(FLAGS) -c TestAllocator.cpp $(TEST_FLAGS)

allocator: main.o Allocator.o
	$(CC) $(FLAGS) -o Allocator.out main.o Allocator.o

main.o: main.cpp Allocator.hpp
	$(CC) $(FLAGS) -c main.cpp

allocator.o: Allocator.cpp Allocator.hpp
	$(CC) $(FLAGS) -c Allocator.cpp

clean:
	rm -rf *.o *.out *.a 
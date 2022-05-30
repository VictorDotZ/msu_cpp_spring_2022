CC=g++
FLAGS=-std=c++2a -Wall -Werror -Wunused-variable -Wsign-conversion -Wextra -fsanitize=address
TEST_FLAGS=-lgtest -lpthread

all: test

test: TestFormat.o
	$(CC) $(FLAGS) -o Test.out TestFormat.o $(TEST_FLAGS)
	./Test.out

TestFormat.o: TestFormat.cpp Format.hpp
	$(CC) $(FLAGS) -c TestFormat.cpp

clean:
	rm -rf *.o *.out *.a 
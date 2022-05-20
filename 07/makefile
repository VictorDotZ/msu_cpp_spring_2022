CC=g++
FLAGS=-std=c++2a -Wall -Werror -Wunused-variable -Wsign-conversion -Wextra -fsanitize=address 
TEST_FLAGS=-lgtest -lpthread

all: test

test: TestVector.o
	$(CC) $(FLAGS) -o Test.out TestVector.o $(TEST_FLAGS)
	./Test.out

TestVector.o: TestVector.cpp Vector.hpp
	$(CC) $(FLAGS) -c TestVector.cpp

clean:
	rm -rf *.o *.out *.a
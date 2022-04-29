CC=g++
FLAGS=-std=c++2a -Wall -Werror -Wunused-variable -Wsign-conversion -Wextra -fsanitize=address
TEST_FLAGS=-lgtest -lpthread

all: test

test: TestMatrix.o Matrix.o
	$(CC) $(FLAGS) -o Test.out TestMatrix.o Matrix.o $(TEST_FLAGS)
	./Test.out

TestMatrix.o: TestMatrix.cpp Matrix.hpp
	$(CC) $(FLAGS) -c TestMatrix.cpp

Matrix.o: Matrix.cpp Matrix.hpp
	$(CC) $(FLAGS) -c Matrix.cpp

clean:
	rm -rf *.o *.out *.a
CC=g++
FLAGS=-std=c++2a -Wall -Werror -Wunused-variable -Wsign-conversion -Wextra -fsanitize=address -pthread
TEST_FLAGS=-lgtest -lpthread 

all: test

test: TestFileSort.o FileSort.o 
	$(CC) $(FLAGS) -o Test.out TestFileSort.o FileSort.o $(TEST_FLAGS)
	./Test.out

TestFileSort.o: TestFileSort.cpp FileSort.hpp
	$(CC) $(FLAGS) -c TestFileSort.cpp

FileSort.o: FileSort.cpp FileSort.hpp
	$(CC) $(FLAGS) -c FileSort.cpp

clean:
	rm -rf *.o *.out *.a
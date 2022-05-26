CC=g++
FLAGS=-std=c++2a -Wall -Werror -Wunused-variable -Wsign-conversion -Wextra -fsanitize=address -pthread
TEST_FLAGS=-lgtest -lpthread 

all: test

test: TestThreadPool.o ThreadPool.o 
	$(CC) $(FLAGS) -o Test.out TestThreadPool.o ThreadPool.o $(TEST_FLAGS)
	./Test.out

TestThreadPool.o: TestThreadPool.cpp ThreadPool.hpp
	$(CC) $(FLAGS) -c TestThreadPool.cpp 

ThreadPool.o: ThreadPool.cpp ThreadPool.hpp
	$(CC) $(FLAGS) -c ThreadPool.cpp

clean:
	rm -rf *.o *.out *.a
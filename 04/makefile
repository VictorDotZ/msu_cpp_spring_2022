CC=g++
FLAGS=-std=c++2a -Wall -Werror -Wunused-variable -Wsign-conversion -Wextra -fsanitize=address
TEST_FLAGS=-lgtest -lpthread

all: test

test: TestBigInt.o BigInt.o
	$(CC) $(FLAGS) -o Test.out TestBigInt.o BigInt.o $(TEST_FLAGS)
	./Test.out

TestBigInt.o: TestBigInt.cpp BigInt.hpp
	$(CC) $(FLAGS) -c TestBigInt.cpp

BigInt.o: BigInt.cpp BigInt.hpp
	$(CC) $(FLAGS) -c BigInt.cpp

clean:
	rm -rf *.o *.out *.a
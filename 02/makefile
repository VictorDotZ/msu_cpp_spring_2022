CC=g++
FLAGS=-std=c++2a -Wall -Werror -Wunused-variable -Wsign-conversion -Wextra -fsanitize=address
TEST_FLAGS=-lgtest -lpthread

all: test

test: TestTokenParser.o TokenParser.o
	$(CC) $(FLAGS) -o Test.out TestTokenParser.o TokenParser.o $(TEST_FLAGS)
	./Test.out

TestTokenParser.o: TestTokenParser.cpp TokenParser.hpp
	$(CC) $(FLAGS) -c TestTokenParser.cpp

TokenParser.o: TokenParser.cpp TokenParser.hpp
	$(CC) $(FLAGS) -c TokenParser.cpp

clean:
	rm -rf *.o *.out *.a 
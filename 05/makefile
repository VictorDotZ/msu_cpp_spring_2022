CC=g++
FLAGS=-std=c++2a -Wall -Werror -Wunused-variable -Wsign-conversion -Wextra -fsanitize=address 
TEST_FLAGS=-lgtest -lpthread

all: test

test: TestSerialization.o Deserializer.o Serializer.o
	$(CC) $(FLAGS) -o Test.out TestSerialization.o Deserializer.o Serializer.o $(TEST_FLAGS)
	./Test.out

TestSerialization.o: TestSerialization.cpp Serializer.hpp Deserializer.hpp
	$(CC) $(FLAGS) -c TestSerialization.cpp

Deserializer.o: Deserializer.cpp Deserializer.hpp Error.hpp
	$(CC) $(FLAGS) -c Deserializer.cpp

Serializer.o: Serializer.cpp Serializer.hpp Error.hpp
	$(CC) $(FLAGS) -c Serializer.cpp

clean:
	rm -rf *.o *.out *.a
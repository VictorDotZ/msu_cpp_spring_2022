#include "Queue.hpp"

#include <iostream>

int main()
{
	auto queue = Queue<int>();

	queue.push(3);
	queue.push(4);
	queue.push(5);

	std::cout << queue.front() << std::endl;
	queue.pop();
	std::cout << queue.front() << std::endl;
	queue.pop();
	queue.emplace(10);
	std::cout << queue.front() << std::endl;
	queue.pop();

	std::cout << queue.front() << std::endl;
	queue.pop();
}
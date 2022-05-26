#include "ThreadPool.hpp"

#include <vector>

#include <gtest/gtest.h>

class TestThreadPool : public ::testing::Test {
};

struct A {
};

void foo(const A&) { }

int square(int a)
{
	return a * a;
}

std::string bold(const std::string& s)
{
	return "**" + s + "**";
}

int sum(int a, int b, int c)
{
	return a + b + c;
}

TEST_F(TestThreadPool, common)
{
	std::vector<int> vector;
	ThreadPool pool(std::thread::hardware_concurrency());

	for (int i = -10; i < 10; ++i) {
		auto task = pool.exec(square, i);
		vector.push_back(task.get());
	}

	int j = -10;
	for (size_t i = 0; i < vector.size(); ++i, ++j)
		ASSERT_EQ(vector[i], j * j);
}

TEST_F(TestThreadPool, private)
{
	ThreadPool pool(8);

	auto task1 = pool.exec(foo, A());
	task1.get();

	auto task2 = pool.exec([]() { return 1; });
	ASSERT_EQ(task2.get(), 1);

	auto task3 = pool.exec(square, 5);
	ASSERT_EQ(task3.get(), 25);

	auto task4 = pool.exec(bold, "lorem ipsum");
	ASSERT_EQ(task4.get(), "**lorem ipsum**");

	for (int i = 1; i <= 10; ++i) {
		auto task = pool.exec(sum, i, -i, 1);
		ASSERT_EQ(task.get(), 1);
	}
}

int main(int argc, char* argv[])
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
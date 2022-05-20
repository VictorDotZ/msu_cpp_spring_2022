#include "Vector.hpp"
#include <cassert>
#include <iostream>
#include <vector>

#include <gtest/gtest.h>

class TestVector : public ::testing::Test {
};

TEST_F(TestVector, IndexingAfterEmptyResized)
{
	Vector<int> vector;
	ASSERT_TRUE(vector.empty());
	ASSERT_EQ(vector.size(), 0);

	vector.resize(3);
	ASSERT_FALSE(vector.empty());
	ASSERT_EQ(vector.size(), 3);

	vector[0] = 10;
	vector[1] = -10;

	ASSERT_EQ(vector[0], 10);
	ASSERT_EQ(vector[1], -10);
	ASSERT_EQ(vector[2], 0);

	vector[0] = 100;
	vector[1] = -100;
	vector[2] = 999;

	ASSERT_EQ(vector[0], 100);
	ASSERT_EQ(vector[1], -100);
	ASSERT_EQ(vector[2], 999);
}

TEST_F(TestVector, PushPopBack)
{
	Vector<int> vector;
	ASSERT_TRUE(vector.empty());
	ASSERT_EQ(vector.size(), 0);

	vector.push_back(10);

	ASSERT_FALSE(vector.empty());
	ASSERT_EQ(vector.size(), 1);
	ASSERT_EQ(vector[0], 10);

	vector.push_back(20);
	vector.push_back(30);
	ASSERT_EQ(vector.size(), 3);
	ASSERT_EQ(vector[2], 30);

	vector.pop_back();
	vector.pop_back();
	ASSERT_EQ(vector.size(), 1);

	vector.push_back(40);
	vector.push_back(50);
	ASSERT_EQ(vector.size(), 3);
	ASSERT_EQ(vector[2], 50);
}

TEST_F(TestVector, BeginEnd)
{
	Vector<int> vector;
	for (int i = 0; i < 3; ++i)
		vector.push_back(i);

	auto begin = vector.begin();
	ASSERT_EQ(*begin, 0);
	ASSERT_NE(begin, vector.end());

	begin++;
	ASSERT_EQ(*begin, 1);
	ASSERT_NE(begin, vector.end());

	++begin;
	ASSERT_EQ(*begin, 2);
	ASSERT_NE(begin, vector.end());

	begin += 1;
	ASSERT_EQ(begin, vector.end());

	begin -= vector.size();
	ASSERT_EQ(begin, vector.begin());

	begin += vector.size();
	ASSERT_EQ(begin, vector.end());

	begin--;
	ASSERT_EQ(*begin, 2);
	ASSERT_NE(begin, vector.end());

	--begin;
	ASSERT_EQ(*begin, 1);
	ASSERT_NE(begin, vector.end());
}

TEST_F(TestVector, RbeginRend)
{
	Vector<int> vector;
	for (int i = 0; i < 3; ++i)
		vector.push_back(i);

	auto rbegin = vector.rbegin();
	ASSERT_EQ(*rbegin, 2);
	ASSERT_NE(rbegin, vector.rend());

	rbegin++;
	ASSERT_EQ(*rbegin, 1);
	ASSERT_NE(rbegin, vector.rend());

	++rbegin;
	ASSERT_EQ(*rbegin, 0);
	ASSERT_NE(rbegin, vector.rend());

	rbegin += 1;
	ASSERT_EQ(rbegin, vector.rend());

	rbegin -= vector.size();
	ASSERT_EQ(rbegin, vector.rbegin());

	rbegin += vector.size();
	ASSERT_EQ(rbegin, vector.rend());

	rbegin--;
	ASSERT_EQ(*rbegin, 0);
	ASSERT_NE(rbegin, vector.rend());

	--rbegin;
	ASSERT_EQ(*rbegin, 1);
	ASSERT_NE(rbegin, vector.rend());
}

struct Item {
	int a, b, c;
	Item()
	    : a(0)
	    , b(0)
	    , c(0)
	{
	}
	Item(int a, int b, int c)
	    : a(a)
	    , b(b)
	    , c(c)
	{
	}
};

TEST_F(TestVector, EmplaceBack)
{
	Vector<Item> vector;

	vector.emplace_back(1, 2, 3);
	ASSERT_EQ(vector.size(), 1);
	ASSERT_EQ(vector[0].a, 1);
	ASSERT_EQ(vector[0].b, 2);
	ASSERT_EQ(vector[0].c, 3);

	vector.emplace_back(10, 20, 30);
	ASSERT_EQ(vector.size(), 2);
	ASSERT_EQ(vector[1].a, 10);
	ASSERT_EQ(vector[1].b, 20);
	ASSERT_EQ(vector[1].c, 30);
}

TEST_F(TestVector, Reserve)
{
	Vector<int> vector;

	ASSERT_TRUE(vector.empty());

	vector.push_back(10);
	vector.emplace_back(20);

	ASSERT_EQ(vector.size(), 2);
	ASSERT_EQ(vector.capacity(), 2);

	vector.reserve(3);
	ASSERT_EQ(vector.size(), 2);
	ASSERT_EQ(vector.capacity(), 3);

	ASSERT_EQ(vector[0], 10);
	ASSERT_EQ(vector[1], 20);
}

TEST_F(TestVector, OutOfRange)
{
	Vector<int> vector;
	vector.resize(10);

	EXPECT_NO_THROW(vector[9]);
	EXPECT_THROW(vector[10], std::out_of_range);
	EXPECT_THROW(vector[100], std::out_of_range);
}

int main(int argc, char* argv[])
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
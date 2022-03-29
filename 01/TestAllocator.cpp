#include "Allocator.hpp"

#include <gtest/gtest.h>

class TestAllocator : public ::testing::Test {
protected:
	void SetUp()
	{
		allocator = new Allocator();
	}

	void TearDown()
	{
		delete allocator;
	}
	Allocator* allocator;
};

TEST_F(TestAllocator, makeAllocator)
{
	size_t size = 5000;
	allocator->makeAllocator(size);

	ASSERT_EQ(allocator->size(), size);
	ASSERT_EQ(allocator->offset(), 0);
	ASSERT_NE(allocator->ptr(), nullptr);

	size += 200;
	allocator->makeAllocator(size);

	ASSERT_EQ(allocator->size(), size);
	ASSERT_EQ(allocator->offset(), 0);
	ASSERT_NE(allocator->ptr(), nullptr);
}

TEST_F(TestAllocator, alloc)
{
	size_t allocatedSize = 5000;
	allocator->makeAllocator(allocatedSize);

	size_t size1 = 1000;

	ASSERT_NE(allocator->alloc(size1), nullptr);
	ASSERT_EQ(allocator->offset(), size1);

	size_t size2 = 2000;

	ASSERT_NE(allocator->alloc(size2), nullptr);
	ASSERT_EQ(allocator->offset(), size2 + size1);

	size_t size3 = 3000;

	ASSERT_EQ(allocator->alloc(size3), nullptr);
}

TEST_F(TestAllocator, reset)
{
	size_t allocatedSize = 5000;
	allocator->makeAllocator(allocatedSize);

	size_t size1 = 1000;
	allocator->alloc(size1);

	allocator->reset();

	ASSERT_EQ(allocator->offset(), 0);
}

int main(int argc, char* argv[])
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
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
	allocator->makeAllocator(0);

	ASSERT_EQ(allocator->size(), 0);
	ASSERT_EQ(allocator->offset(), 0);
	ASSERT_EQ(allocator->ptr(), nullptr);

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

	allocator->makeAllocator(size);

	ASSERT_EQ(allocator->size(), size);
	ASSERT_EQ(allocator->offset(), 0);
	ASSERT_NE(allocator->ptr(), nullptr);
}

TEST_F(TestAllocator, alloc)
{
	size_t allocatedSize = 5000;

	char* ptr1 = allocator->alloc(allocatedSize);
	ASSERT_EQ(ptr1, nullptr);
	ASSERT_EQ(allocator->ptr(), nullptr);
	ASSERT_EQ(allocator->offset(), 0);
	ASSERT_EQ(allocator->size(), 0);

	allocator->makeAllocator(allocatedSize);

	char* ptr2 = allocator->alloc(0);
	ASSERT_EQ(ptr2, nullptr);
	ASSERT_EQ(allocator->offset(), 0);

	char* ptr3 = allocator->alloc(allocatedSize);
	ASSERT_NE(ptr3, nullptr);
	ASSERT_EQ(allocator->offset(), allocatedSize);
	ASSERT_EQ(ptr3 - allocator->ptr(), 0);

	char* ptr4 = allocator->alloc(1);
	ASSERT_EQ(ptr4, nullptr);
	ASSERT_EQ(allocator->offset(), allocatedSize);

	allocator->reset();

	size_t size1 = 1000;

	char* ptr5 = allocator->alloc(size1);
	ASSERT_NE(ptr5, nullptr);
	ASSERT_EQ(allocator->offset(), size1);
	ASSERT_EQ(ptr5 - allocator->ptr(), 0);

	size_t size2 = 2000;

	char* ptr6 = allocator->alloc(size2);
	ASSERT_NE(ptr6, nullptr);
	ASSERT_EQ(allocator->offset(), size2 + size1);
	ASSERT_EQ(ptr6 - allocator->ptr(), size1);
	ASSERT_EQ(ptr6 - ptr5, size1);

	size_t size3 = 3000;

	char* ptr7 = allocator->alloc(size3);
	ASSERT_EQ(ptr7, nullptr);
	ASSERT_EQ(allocator->offset(), size1 + size2);

	size_t size4 = 2000;

	char* ptr8 = allocator->alloc(size4);
	ASSERT_NE(ptr8, nullptr);
	ASSERT_EQ(allocator->offset(), size4 + size2 + size1);
	ASSERT_EQ(ptr8 - allocator->ptr(), size1 + size2);
	ASSERT_EQ(ptr8 - ptr6, size2);

	char* ptr9 = allocator->alloc(1);
	ASSERT_EQ(ptr9, nullptr);
	ASSERT_EQ(allocator->offset(), allocatedSize);

	allocator->reset();

	char* ptr10 = allocator->alloc(allocatedSize);
	ASSERT_NE(ptr10, nullptr);
	ASSERT_EQ(allocator->offset(), allocatedSize);
	ASSERT_EQ(ptr10 - allocator->ptr(), 0);
}

TEST_F(TestAllocator, reset)
{
	size_t allocatedSize = 5000;
	allocator->makeAllocator(allocatedSize);

	size_t size1 = 1000;
	allocator->alloc(size1);

	allocator->reset();

	ASSERT_EQ(allocator->offset(), 0);

	allocator->alloc(allocatedSize);

	allocator->reset();

	ASSERT_EQ(allocator->offset(), 0);
}

int main(int argc, char* argv[])
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
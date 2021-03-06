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

TEST_F(TestAllocator, reallocationThroughDelete)
{
	size_t allocatedSize = 5000;
	allocator->makeAllocator(allocatedSize);

	const char* ptr1 = allocator->ptr();
	const char* ptr2 = allocator->alloc(allocatedSize);

	ASSERT_EQ(ptr1, ptr2);

	const char* ptr3 = ptr2;

	allocatedSize += 5000;
	allocator->makeAllocator(allocatedSize);

	ASSERT_EQ(allocator->alloc(allocatedSize), allocator->ptr());

	ASSERT_NE(ptr3, allocator->ptr());
}

TEST_F(TestAllocator, reallocationThroughMakeAllocator)
{
	size_t size1 = 5000;
	allocator->makeAllocator(size1);

	ASSERT_EQ(allocator->size(), size1);
	ASSERT_EQ(allocator->offset(), 0);
	ASSERT_NE(allocator->ptr(), nullptr);

	const char* ptr1 = allocator->alloc(size1 - 1);
	ASSERT_EQ(allocator->offset(), size1 - 1);

	const char* ptr2 = allocator->alloc(1);
	ASSERT_EQ(allocator->offset(), size1);
	ASSERT_EQ(ptr2 - ptr1, size1 - 1);

	size_t size2 = size1 + 200;
	allocator->makeAllocator(size2);

	ASSERT_EQ(allocator->size(), size2);
	ASSERT_EQ(allocator->offset(), 0);
	ASSERT_NE(allocator->ptr(), nullptr);

	const char* ptr3 = allocator->alloc(size2 - 1);
	ASSERT_EQ(allocator->offset(), size2 - 1);

	const char* ptr4 = allocator->alloc(1);
	ASSERT_EQ(allocator->offset(), size2);
	ASSERT_EQ(ptr4 - ptr3, size2 - 1);
	ASSERT_NE(size1, size2);
}

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

	const char* ptr1 = allocator->alloc(allocatedSize);
	ASSERT_EQ(ptr1, nullptr);
	ASSERT_EQ(allocator->ptr(), nullptr);
	ASSERT_EQ(allocator->offset(), 0);
	ASSERT_EQ(allocator->size(), 0);

	allocator->makeAllocator(allocatedSize);

	const char* ptr2 = allocator->alloc(0);
	ASSERT_EQ(ptr2, nullptr);
	ASSERT_EQ(allocator->offset(), 0);

	const char* ptr3 = allocator->alloc(allocatedSize);
	ASSERT_NE(ptr3, nullptr);
	ASSERT_EQ(allocator->offset(), allocatedSize);
	ASSERT_EQ(ptr3 - allocator->ptr(), 0);

	const char* ptr4 = allocator->alloc(1);
	ASSERT_EQ(ptr4, nullptr);
	ASSERT_EQ(allocator->offset(), allocatedSize);

	allocator->reset();

	size_t size1 = 1000;

	const char* ptr5 = allocator->alloc(size1);
	ASSERT_NE(ptr5, nullptr);
	ASSERT_EQ(allocator->offset(), size1);
	ASSERT_EQ(ptr5 - allocator->ptr(), 0);

	size_t size2 = 2000;

	const char* ptr6 = allocator->alloc(size2);
	ASSERT_NE(ptr6, nullptr);
	ASSERT_EQ(allocator->offset(), size2 + size1);
	ASSERT_EQ(ptr6 - allocator->ptr(), size1);
	ASSERT_EQ(ptr6 - ptr5, size1);

	size_t size3 = 3000;

	const char* ptr7 = allocator->alloc(size3);
	ASSERT_EQ(ptr7, nullptr);
	ASSERT_EQ(allocator->offset(), size1 + size2);

	size_t size4 = 2000;

	const char* ptr8 = allocator->alloc(size4);
	ASSERT_NE(ptr8, nullptr);
	ASSERT_EQ(allocator->offset(), size4 + size2 + size1);
	ASSERT_EQ(ptr8 - allocator->ptr(), size1 + size2);
	ASSERT_EQ(ptr8 - ptr6, size2);

	const char* ptr9 = allocator->alloc(1);
	ASSERT_EQ(ptr9, nullptr);
	ASSERT_EQ(allocator->offset(), allocatedSize);

	allocator->reset();

	const char* ptr10 = allocator->alloc(allocatedSize);
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
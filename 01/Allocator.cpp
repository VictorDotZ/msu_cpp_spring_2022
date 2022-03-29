#include "Allocator.hpp"

void Allocator::makeAllocator(size_t maxSize)
{
	if (this->m_ptr != nullptr)
		delete[] this->m_ptr;

	this->m_ptr = new char[maxSize];
	this->m_offset = 0;
	this->m_size = maxSize;
}

char* Allocator::alloc(size_t size)
{
	if (size + this->m_offset > this->m_size)
		return nullptr;

	this->m_offset += size;

	return this->m_ptr + (this->m_offset - size);
}

void Allocator::reset()
{
	this->m_offset = 0;
}

const char* Allocator::ptr()
{
	return this->m_ptr;
}

size_t Allocator::offset()
{
	return this->m_offset;
}

size_t Allocator::size()
{
	return this->m_size;
}

Allocator::~Allocator()
{
	delete[] this->m_ptr;
}

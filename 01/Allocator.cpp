#include "Allocator.hpp"

void Allocator::makeAllocator(size_t maxSize)
{
	if (maxSize == 0)
		return;

	if (m_ptr != nullptr)
		delete[] m_ptr;

	m_ptr = new char[maxSize];
	m_offset = 0;
	m_size = maxSize;
}

char* Allocator::alloc(size_t size)
{
	if ((size + m_offset > m_size) || (size == 0) || (m_ptr == nullptr))
		return nullptr;

	m_offset += size;

	return m_ptr + (m_offset - size);
}

void Allocator::reset()
{
	m_offset = 0;
}

const char* Allocator::ptr()
{
	return m_ptr;
}

size_t Allocator::offset()
{
	return m_offset;
}

size_t Allocator::size()
{
	return m_size;
}

Allocator::~Allocator()
{
	delete[] m_ptr;
}

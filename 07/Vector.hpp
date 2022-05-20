#pragma once

#include "Iterator.hpp"

#include "Allocator.hpp"

template <class T, class Alloc = Allocator<T>>
class Vector {
public:
	Vector()
	    : m_alloc(Alloc())
	    , m_size(0)
	    , m_capacity(0)
	    , m_data(m_alloc.allocate(m_size))
	    , m_start(m_data)
	    , m_end(m_data)
	{
	}

	template <class... Args>
	void emplace_back(Args&&... args)
	{
		T obj(std::forward<Args>(args)...);
		push_back(obj);
	}

	T& operator[](uint32_t i)
	{
		if (i >= size())
			throw std::out_of_range("");
		return m_data[i];
	}

	const T& operator[](uint32_t i) const
	{
		if (i >= size())
			throw std::out_of_range("");
		return m_data[i];
	}

	void push_back(const T& value)
	{
		if (m_size == m_capacity) {
			if (m_capacity == 0)
				reserve(1);
			else
				reserve(m_capacity * 2);
		}
		m_alloc.construct(m_end++, value);
		m_size++;
	}

	void pop_back()
	{
		if (m_size > 0) {
			m_alloc.destroy(--m_end);
			m_size--;
		}
	}

	bool empty() const
	{
		return m_start == m_end;
	}

	uint32_t size() const
	{
		return m_size;
	}

	uint32_t capacity() const
	{
		return m_capacity;
	}

	void clear()
	{
		resize(0);
	}

	void resize(uint32_t size)
	{
		if (m_size < size)
			reserve(size);

		Iterator<T> prev = m_end;
		m_end = m_start + size;

		while (prev > m_end)
			m_alloc.destroy(--prev);

		while (prev < m_end)
			m_alloc.construct(prev++, T());

		m_size = size;
	}

	void reserve(uint32_t capacity)
	{
		if (capacity > m_capacity) {
			T* buffer = m_alloc.allocate(capacity);
			for (uint32_t i = 0; i < this->size(); ++i) {
				m_alloc.construct(buffer + i, std::move(m_data[i]));
				m_alloc.destroy(m_data + i);
			}
			m_alloc.deallocate(m_data);
			m_data = buffer;
			m_start = Iterator<T>(m_data);
			m_end = m_start + this->size();
			m_capacity = capacity;
		}
	}

	~Vector()
	{
		for (T* ptr = m_data; ptr < m_data + size(); ++ptr)
			m_alloc.destroy(ptr);

		m_alloc.deallocate(m_data);
	}

	Iterator<T> begin()
	{
		return m_start;
	}

	Iterator<T> end()
	{
		return m_end;
	}

	std::reverse_iterator<Iterator<T>> rbegin()
	{
		return std::reverse_iterator<Iterator<T>>(m_end);
	}

	std::reverse_iterator<Iterator<T>> rend()
	{
		return std::reverse_iterator<Iterator<T>>(m_start);
	}

private:
	Alloc m_alloc;

	uint32_t m_size;
	uint32_t m_capacity;
	T* m_data;

	Iterator<T> m_start;
	Iterator<T> m_end;
};
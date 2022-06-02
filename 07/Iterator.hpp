#pragma once

#include <iterator>

template <class T>
class Iterator : public std::iterator<std::random_access_iterator_tag, T> {
public:
	Iterator(T* ptr)
	    : m_ptr(ptr)
	{
	}

	operator T*()
	{
		return m_ptr;
	}

	T& operator*()
	{
		return *m_ptr;
	}

	T& operator[](std::ptrdiff_t n)
	{
		return *(m_ptr + n);
	}

	Iterator<T>& operator++()
	{
		m_ptr++;
		return *this;
	}

	Iterator<T> operator++(int)
	{
		Iterator<T> tmp = *this;
		++*this;
		return tmp;
	}

	Iterator<T>& operator--()
	{
		m_ptr--;
		return *this;
	}

	Iterator<T> operator--(int)
	{
		Iterator<T> tmp = *this;
		--*this;
		return tmp;
	}

	Iterator<T>& operator+=(std::ptrdiff_t n)
	{
		m_ptr += n;
		return *this;
	}

	Iterator<T>& operator-=(std::ptrdiff_t n)
	{
		m_ptr -= n;
		return *this;
	}

	Iterator<T> operator+(std::ptrdiff_t n) const
	{
		return Iterator<T>(m_ptr + n);
	}

	Iterator<T> operator-(std::ptrdiff_t n) const
	{
		return Iterator<T>(m_ptr - n);
	}

	std::ptrdiff_t operator-(const Iterator<T>& it) const
	{
		return m_ptr - it.m_ptr;
	}

	bool operator==(const Iterator<T>& it) const
	{
		return m_ptr == it.m_ptr;
	}

	bool operator!=(const Iterator<T>& it) const
	{
		return m_ptr != it.m_ptr;
	}

private:
	T* m_ptr;
};

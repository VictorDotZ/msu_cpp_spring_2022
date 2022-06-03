#pragma once

#include <deque>

template <class T>
class Queue {
public:
	Queue()
	{
		m_deque = new std::deque<T>();
	}
	~Queue()
	{
		delete m_deque;
	}

	void push(const T& elem)
	{
		m_deque->push_back(elem);
	}

	T& front()
	{
		return m_deque->front();
	}

	void pop()
	{
		m_deque->pop_front();
	}

	size_t size() const
	{
		return m_deque->size();
	}

	template <class... Args>
	void emplace(Args&&... args)
	{
		push(T(std::forward<Args>(args)...));
	}

private:
	std::deque<T>* m_deque;
};
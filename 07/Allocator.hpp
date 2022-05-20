#pragma once

template <class T>
class Allocator {
public:
	T* allocate(size_t count)
	{
		T* data = new T[count];
		if (data == nullptr)
			throw std::bad_alloc();
		return data;
	}

	void deallocate(T* ptr)
	{
		delete[] ptr;
	}

	template <typename... Args>
	void construct(T* ptr, Args&&... args)
	{
		new (ptr) T(std::forward<Args>(args)...);
	}

	void destroy(T* ptr)
	{
		ptr->~T();
	}
};

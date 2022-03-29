#pragma once
#include <cstddef>

class Allocator {
private:
    char* m_ptr = nullptr;
    size_t m_offset = 0;
    size_t m_size = 0;

public:
    void makeAllocator(size_t maxSize);
    char* alloc(size_t size);
    void reset();

    ~Allocator();
};
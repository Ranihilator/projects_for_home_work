#pragma once

#include <cstdint>
#include <cstddef>
#include <new>

namespace ALLOCATOR
{

extern std::size_t alloc_counter;
void* malloc(std::size_t size) throw (std::bad_alloc)
{
    void* p = std::malloc(size);
    std::cout << "malloc: " << ++alloc_counter << " " << std::hex << p << std::dec << " "  << size << " "  << std::endl;
    return p;
}
void free(void* p) noexcept
{
    std::cout << "free: " << --alloc_counter << " " << std::hex << p << std::endl;
    std::free(p);
    return;
}

}

inline void* operator new(std::size_t size) throw (std::bad_alloc)
{
    return ALLOCATOR::malloc(size);
}

inline void operator delete(void* p) noexcept
{
    ALLOCATOR::free(p);
}

inline void* operator new[](std::size_t size) throw (std::bad_alloc)
{
    return ALLOCATOR::malloc(size);
}

inline void operator delete[](void* p) throw()
{
    ALLOCATOR::free(p);
}

inline void* operator new(std::size_t size, const std::nothrow_t&) noexcept
{
    return ALLOCATOR::malloc(size);
}

inline void operator delete(void* p, const std::nothrow_t&) noexcept
{
    ALLOCATOR::free(p);
}

inline void* operator new[](std::size_t size, const std::nothrow_t&) noexcept
{
    return ALLOCATOR::malloc(size);
}

inline void operator delete[](void* p, const std::nothrow_t&) noexcept
{
    ALLOCATOR::free(p);
}

inline void operator delete(void* p, long unsigned int)
{
    ALLOCATOR::free(p);
}

inline void operator delete [](void* p, long unsigned int)
{
    ALLOCATOR::free(p);
}

/*!
\file
\brief overload malloc free
 */
#pragma once

#include <cstdint>
#include <cstddef>
#include <new>

namespace HW_03
{

namespace ALLOCATOR
{

extern std::size_t alloc_counter;   ///< counter of memory allocated

/*!
\brief malloc
\see alloc_counter
\param[in] size size of allocated memory
\return pointer to allocated memory
*/
void* malloc(std::size_t size) throw (std::bad_alloc)
{
	void* p = std::malloc(size);
	alloc_counter++;
	return p;
}

/*!
\brief free
\see alloc_counter
\param[in] p pointer to allocated memory
\return nothing
*/
void free(void* p) noexcept
{
	alloc_counter--;
	std::free(p);
	return;
}

}

}

extern "C++"
{
	using namespace HW_03;

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

	inline void operator delete[](void* p) throw ()
	{
		ALLOCATOR::free(p);
	}

	inline void* operator new(std::size_t size, const std::nothrow_t&) noexcept{
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
}

#pragma once

#include "manager.h"

namespace ALLOCATOR
{

template <class T, std::size_t arena_size = 1, std::size_t data_size = 10 > //, uint64_t arena_size=1, uint64_t data_size=10
class allocator
{
	ArenaMemoryManager manager;
public:
	using value_type = T;

	allocator() noexcept : manager(arena_size, data_size) { }

	~allocator() { }

public:

	T* allocate(std::size_t n)
	{
		return static_cast<T*> (manager.allocate(n * sizeof (T)));
	}

	void deallocate(T* p, std::size_t n)
	{
		if (p)
			manager.deallocate(p, n * sizeof (T));
	}

	template <class U>
	struct rebind
	{
		using other = allocator<U, arena_size, data_size>;
	};
};

template< class T1, class T2 >
bool operator==(const allocator<T1>& lhs, const allocator<T2>& rhs)
{
	return true;
}

template< class T1, class T2 >
bool operator!=(const allocator<T1>& lhs, const allocator<T2>& rhs)
{
	return false;
}

}

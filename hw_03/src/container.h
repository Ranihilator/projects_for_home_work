/*!
\file
\brief Контайнер
*/
#pragma once

#include "allocator.h" 
#include <iterator>
#include <cstdint>

namespace CONTAINER
{

template<class T, class _A = std::allocator<T>>
class container
{

	struct element_t
	{
		T value;
		element_t *next = nullptr;
	};

public:
	using size_type = std::size_t;

public:

	container() { };

	~container()
	{
		auto mem = element;
		while (mem != nullptr)
		{
			auto next = mem->next;
			traits::destroy(_allocator, &(mem->value));
			traits::deallocate(_allocator, mem, 1);
			mem = next;
		}
		element_size = 0;
	};

	T& operator[](size_type pos)
	{
		if (pos < element_size)
		{
			auto mem = element;
			size_type cur = 0;

			while (mem != nullptr)
			{
				if (cur == pos)
					return mem->value;

				mem = mem->next;
				cur++;
			}
		}
		return element->value;
	}

	size_type size() const
	{
		return element_size;
	}

	bool empty() const
	{
		return (element_size == 0) ? true : false;
	}

	void push_back(const T &value)
	{
		element_t *ptr = traits::allocate(_allocator, 1);

		if (!ptr)
			return;

		traits::construct(_allocator, ptr, element_t {value, nullptr});

		if (!element)
		{
			element = ptr;
			element_size++;
		}
		else
		{
			element_t **mem = &element->next;

			while (*mem != nullptr)
			{
				mem = &(*mem)->next;
			}

			element_size++;
			*mem = ptr;
		}
	}

private:
	using allocator_type = typename std::allocator_traits<_A>::template rebind_alloc<element_t>;
	using traits = std::allocator_traits<allocator_type>;

private:
	element_t *element = nullptr;

	size_type element_size = 0;

	allocator_type _allocator;
};

}



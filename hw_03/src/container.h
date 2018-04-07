/*!
\file
\brief Контайнер
*/
#pragma once

#include "allocator.h"
#include <cstdint>

namespace CONTAINER
{

template<class T, class _A = std::allocator<T>>
class container
{
public:
    using value_type = T;
    using size_type = std::size_t;
    using pointer = T*;
    using const_pointer = const T*;
    using reference = T&;
    using const_reference = const T&;

private:
    struct element_t
    {
        value_type value;
        element_t *next = nullptr;
        element_t *prev = nullptr;
    };

public:
	container()
	{};

	~container()
	{
        clear();
	}

    const_reference at(size_type pos)
    {
        size_type _pos = 0;
        auto element = first;
        while(element)
        {
            if (pos == _pos)
                return element->value;

            _pos++;
            element = element->next;
        }
        std::out_of_range("wrong position");
    }

    void push_back(const_reference value)
    {
        element_t *ptr = traits::allocate(_allocator, 1);

		if (!ptr)
			throw std::length_error("allocator return nullptr");

		traits::construct(_allocator, ptr, element_t {value, nullptr, nullptr});

        if (first)
        {
            auto prev = last;

            last->next = ptr;
            last = ptr;

            last->prev = prev;
        }
        else
            last = first = ptr;

        _size++;
    }

    void pop_back()
    {
        if (last)
        {
            auto del = last;

            last = last->prev;
            last->next = nullptr;

            traits::destroy(_allocator, &(del->value));
			traits::deallocate(_allocator, del, 1);

            _size--;
        }
    }

    void clear()
    {
        while (last)
        {
            auto prev = last->prev;

			traits::destroy(_allocator, &(last->value));
			traits::deallocate(_allocator, last, 1);

			last = prev;
        }
        _size = 0;
        first = last = nullptr;
    }

	size_type size() const
	{
		return _size;
	}

    bool empty() const
	{
		return (size() == 0) ? true : false;
	}

private:
	using allocator_type = typename std::allocator_traits<_A>::template rebind_alloc<element_t>;
	using traits = std::allocator_traits<allocator_type>;

private:
	element_t *first = nullptr;
	element_t *last = nullptr;
	size_type _size = 0;

	allocator_type _allocator;
};

}



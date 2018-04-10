/*!
\file
\brief Контайнер
 */
#pragma once

#include "allocator.h"
#include <cstdint>
#include <functional>

namespace HW_03
{

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
		element_t *prev = nullptr;
	};

	using allocator_type = typename std::allocator_traits<_A>::template rebind_alloc<element_t>;
	using traits = std::allocator_traits<allocator_type>;

public:
	container() : last(nullptr, [&](element_t *ptr)
	{
		while (ptr)
		{
			auto prev = ptr->prev;

			traits::destroy(_allocator, &(ptr->value));
			traits::deallocate(_allocator, ptr, 1);

			ptr = prev;
		}
	})
	{};

	const_reference at(size_type pos)
	{
		size_type _pos = _size;
		auto element = last.get();
		while (element)
		{
			_pos--;

			if (pos == _pos)
				return element->value;

			element = element->prev;
		}
		std::out_of_range("wrong position");
	}

	void push_back(const_reference value)
	{
		element_t *ptr = traits::allocate(_allocator, 1);

		if (!ptr)
			throw std::length_error("allocator return nullptr");

		traits::construct(_allocator, ptr, element_t{value, nullptr});

		if (last)
		{
			auto prev = last.release();

			last.reset(ptr);
			last->prev = prev;
		}
		else
			last.reset(ptr);

		_size++;
	}

	void pop_back()
	{
		if (last)
		{
			auto save = last->prev;
			last->prev = nullptr;

			last.reset(save);

			_size--;
		}
	}

	void clear()
	{
		last.reset(nullptr);
		_size = 0;
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
	allocator_type _allocator;

	std::unique_ptr<element_t, std::function<void(element_t*) >> last;
	size_type _size = 0;

};

}

}


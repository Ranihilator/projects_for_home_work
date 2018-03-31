#pragma once

#include "container.h"

#include <iostream>
#include <map>
#include <type_traits>

constexpr uint64_t factorial(uint64_t n)
{
	return n > 0 ? n * factorial(n - 1) : 1;
}

//type as result for MAP struct
template <class T, class V, std::size_t b = 0, std::size_t d = 0 >
struct MAP
{
	using Type = std::map<T, V, std::less<T>, ALLOCATOR::allocator<std::pair<T, V>, b, d>>;

	Type data;

	void operator()()
	{
		for (auto i = 0; i < 10; ++i)
		{
			data[i] = factorial(i);
		}

		for (auto &i : data)
		{
			std::cout << i.first << " " << i.second << std::endl;
		}
	}
};

template <class T, class V>
struct MAP<T, V, 0, 0>
{
	using Type = std::map<T, V>;

	Type data;

	void operator()()
	{
		for (auto i = 0; i < 10; ++i)
		{
			data[i] = factorial(i);
		}
	}
};




//type as result for CUSTOM_CONTAINER struct
template <class T, std::size_t b = 0, std::size_t d = 0 >
struct CUSTOM_CONTAINER
{
	using Type = CONTAINER::container<T, ALLOCATOR::allocator<T, b, d>>;

	Type data;

	void operator()()
	{
		for (auto i = 0; i < 10; ++i)
		{
			data.push_back(i);
		}

		for (auto i = 0; i < data.size(); ++i)
		{
			std::cout << data[i] << std::endl;
		}
	}
};

template <class T>
struct CUSTOM_CONTAINER<T, 0, 0>
{
	using Type = CONTAINER::container<T>;

	Type data;

	void operator()()
	{
		for (auto i = 0; i < 10; ++i)
		{
			data.push_back(i);
		}
	}
};

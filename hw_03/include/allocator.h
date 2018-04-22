/*!
\file
\brief Allocator
 */
#pragma once

#include <memory>
#include <cstring>
#include <cstdint>
#include <vector>
#include <iostream>
#include <limits>

#ifdef REBIND
#include "memory_rebind.h"
#endif

/// Home work #3 (allocator and containers)
namespace HW_03
{

/// Allocator class
namespace ALLOCATOR
{
#ifdef REBIND
std::size_t alloc_counter = 0;  ///< counter of memory allocated
#endif

using size_type = std::size_t;  ///< Current type of size

/*!
\brief allocator class
\tparam T type of data to memory allocating
\tparam S size of pre allocated memory
*/
template <class T, size_type S = 10 >
class allocator
{
	static_assert(S != 0, "no zero capacity!");

public:
	using value_type = T;                      ///< Current type of data

	using chunks_t = std::vector<uint8_t>;     ///< Current block data

	using blocks_t = std::vector<chunks_t>;    ///< Poll block data

	allocator() noexcept
	{}

	template <class U>
	struct rebind
	{
		using other = allocator<U, S>;
	};

	/*!
	\brief allocate memory to element of type T
	\param[in] n - count element of T
	 */
	T* allocate(size_type n)
	{
		size_type m_available = 0;
		n = n * sizeof (T);

		if (n > std::numeric_limits<uint16_t>::max() || n == 0)
			throw std::bad_alloc();

		if (m_start.capacity() != 0 && m_start.capacity() == m_start.size())
		{
			if (m_blocks.capacity() == 0)
				m_blocks.reserve(S);

			m_blocks.emplace_back(std::move(m_start));
		}

		if (!m_start.empty())
			m_available = m_start.capacity() - m_start.size();

		if (n > m_available)
		{
			if (n > m_start.capacity())
			{
				m_start.reserve(n * S);
				if (m_start.capacity() != n * S)
					throw std::bad_alloc();
			}

			m_available = m_start.capacity();
		}

		uint8_t* m_memory = (uint8_t*) & m_start.back() + 1;
		if (!m_memory)
			throw std::bad_alloc();

		m_start.insert(m_start.end(), n, 0);

		return (T*) m_memory;
	}

	/*!
	\brief freeing memory element type of T
	\param[in] p - Pointer to memory
	\param[in] n - Count of element T
    */
	void deallocate(void* p, size_type n)
	{
		if (p)
		{
			size_type m_available = 0;
			n = n * sizeof (T);

			if (!m_start.empty())
				m_available = m_start.size();

			if (n > m_available && m_blocks.empty())
				return;

			if (m_start.empty())
			{
				if (m_blocks.empty())
					return;

				m_blocks.back().swap(m_start);

				m_available = m_start.size();

				m_blocks.pop_back();
			}

			uint8_t *m_memory = (uint8_t*) & m_start.back() + 1;

			if ((uint8_t*) p + n == m_memory)
				m_start.resize(m_available - n);
			else
				throw std::bad_alloc();
		}
		else
			throw std::bad_alloc();
	}
private:
	blocks_t m_blocks; ///< Poll block data
	chunks_t m_start; ///< Current block data
};

template< class T1, class T2 >
bool operator==(const allocator<T1> &lhs, const allocator<T2> &rhs)
{
	return true;
}

template< class T1, class T2 >
bool operator!=(const allocator<T1> &lhs, const allocator<T2> &rhs)
{
	return false;
}

}

}

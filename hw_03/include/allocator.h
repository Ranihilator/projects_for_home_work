/*!
\file
\brief Аллокатор памяти
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

namespace HW_03
{

namespace ALLOCATOR
{
#ifdef REBIND
std::size_t alloc_counter = 0;
#endif

using size_type = std::size_t;

template <class T, size_type S = 10>
class allocator
{
    static_assert(S != 0, "no zero capacity!");

public:
    using value_type = T;

    using chunks_t = std::vector<uint8_t>; /// Контейнер с данными

    using blocks_t = std::vector<chunks_t>; /// Контейнер блоков данных

    allocator() noexcept
    {}

    template <class U>
    struct rebind
    {
        using other = allocator<U, S>;
    };

    /*!
    @brief Выделить память под элемент T
    @param n - кол-во элементов T
    */
    T* allocate(size_type n)
    {
        size_type m_available = 0;  /// количество свободных элементов в текущем блоке
        n = n * sizeof (T);         /// кол-во элементов -> кол-во байт

        if (n > std::numeric_limits<uint16_t>::max() || n == 0)
            throw std::bad_alloc();

        if (m_start.capacity() != 0 && m_start.capacity() == m_start.size())
        {
            if (m_blocks.capacity()==0)
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

        uint8_t* m_memory = (uint8_t*)&m_start.back() + 1;
        if (!m_memory)
            throw std::bad_alloc();

        m_start.insert(m_start.end(), n, 0);

        return (T*)m_memory;
    }

    /*!
    @brief Освободить память элементов T
    @param p - указатель на память
    @param n - кол-во элементов T
    */
    void deallocate(void* p, size_type n)
    {
        if (p)
        {
            size_type m_available = 0;  /// количество свободных элементов в текущем блоке
            n = n * sizeof (T);         /// кол-во элементов -> кол-во байт

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

            uint8_t *m_memory = (uint8_t*)&m_start.back() + 1;

            if ((uint8_t*)p + n == m_memory)
                m_start.resize(m_available - n);
            else
                throw std::bad_alloc();
        }
        else
            throw std::bad_alloc();
    }

private:
    blocks_t m_blocks;      /// Блок последующих данных
    chunks_t m_start;       /// Текущий блок данных
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

}

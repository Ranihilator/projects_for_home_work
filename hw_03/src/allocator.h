#pragma once

#include <memory>
#include <cstring>
#include <cstdint>
#include <vector>
#include <iostream>

#ifdef REBIND
#include "memory_rebind.h"
#endif

namespace ALLOCATOR
{
#ifdef REBIND
std::size_t alloc_counter = 0;
#endif

using size_type = std::size_t;

template <class T, size_type A = 1, size_type S = 10 >
class allocator
{
public:
    using value_type = T;

    using chunk_t  = std::vector<uint8_t>; /// блок данных
    using chunks_t = std::vector<chunk_t>; /// Контейнер для хранения блоков данных

    /*!
    @brief конструктор по умолчанию
    @param arena_size - кол-во блоков
    @param size - кол-во байтов в блоке
    */
    allocator() noexcept
    {
        m_chunks.reserve(A);
    }

    /*!
    @brief конструктор копирования
    @detailed выделет память под новые данные
    */
    allocator(const allocator &other);


    /*!
    @brief оператор копирования
    @detailed освобождает выделеную память из общей кучи и заново выделет память под новые данные
    */
    allocator& operator=(const allocator &other)
    {
        m_chunks.clear();

        if (m_chunks.capacity() < other.m_chunks.capacity())
        {
            m_chunks.reserve(other.capacity());
        }

        for (decltype(m_chunks.size()) i = 0; i < m_chunks.size(); ++i)
        {
            m_chunks.emplace_back(chunk_t());
            m_chunks.back().reserve(other.m_chunks[i].capacity());
            m_chunks.back() = other.m_chunk[i];

        }

        return *this;
    }

public:

    /*!
    @brief выделить блок данных с указанием кол-во байт из общей кучи
    @param n - кол-во байт
    \return Nothing
     */
    T* allocate(size_type n);

    /*!
    @brief освободить блок данных с указанием кол-во байт в общую кучу
    @param p - указатель на блок данных
    @param n - кол-во байт
    \return Nothing
     */
    void deallocate(T* p, size_type n);

    template <class U>
    struct rebind
    {
        using other = allocator<U, A, S>;
    };

private:
    chunks_t m_chunks; ///Данные
    uint8_t* m_memory = nullptr; ///указатель на текущую позицию в блоке данных

    size_type m_available = 0; ///Сколько байт свободно в куче
};

template <class T, size_type arena_size, size_type size>
allocator<T, arena_size, size>::allocator(const allocator &other)// : m_chunks(std::vector<chunk_t>(other.m_chunks.capacity()))
{
    for (decltype(m_chunks.size()) i = 0; i < m_chunks.size(); ++i)
    {
        m_chunks.emplace_back(chunk_t());
        m_chunks.back().reserve(other.m_chunks[i].capacity());
        m_chunks.back() = other.m_chunks[i];
    }
}

template <class T, size_type A, size_type S>
void allocator<T, A, S>::deallocate(T* p, size_type n)
{
    if (p)
    {
        n = n * sizeof (T);
        auto mem = (uint8_t*) p;

        if (mem + n == m_memory)
        {
            m_memory = mem;
            m_available += n;
        }
    }
}

template <class T, size_type A, size_type S>
T* allocator<T, A, S>::allocate(size_type n)
{
    n = n * sizeof (T);
    if (n > m_available)
    {
        m_chunks.emplace_back(chunk_t());

        m_chunks.back().reserve(n * S);
        m_available = m_chunks.back().capacity();

        if (m_available != n * S)
            std::bad_alloc();

        m_memory = m_chunks.back().data();
    }

    auto mem = m_memory;
    m_available -= n;
    m_memory += n;
    return (T*)mem;
}

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

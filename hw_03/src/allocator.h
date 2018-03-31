#pragma once

#include "manager.h"

namespace ALLOCATOR
{
using size_type = std::size_t;

template <class T, size_type A = 1, size_type S = 10 >
class allocator
{
public:
    using value_type = T;


    using chunk_t = std::pair<size_type, uint8_t*>; /// блок данных (размер блока, данные)
    using chunks_t = PointerManager<chunk_t>; /// Контейнер для хранения блоков данных


    /*!
    @brief конструктор по умолчанию
    @detailed выделяет память в куче под новые данные
    @param arena_size - кол-во блоков
    @param size - кол-во байтов в блоке
    */
    allocator() noexcept : m_chunks(A), m_size(S)
    {}

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
        for (decltype(m_chunks.pos) i = 0; i < m_chunks.pos; ++i)
        {
            std::free(std::get<1>(*m_chunks.data(i)));
        }
        m_chunks.pos = 0;

        if (m_chunks.size < other.m_chunks.size)
        {
            m_chunks = PointerManager<chunk_t>(other.m_chunks.size);
        }

        for (decltype(m_chunks.pos) i = 0; i < m_chunks.pos; ++i)
        {
            chunk_t data;
            data = std::make_pair(std::get<0>(*other.m_chunks.data(i)), (uint8_t*) std::malloc(std::get<0>(*other.m_chunks.data(i))));

            std::memcpy(std::get<1>(data), std::get<1>(*other.m_chunks.data(i)), std::get<0>(*other.m_chunks.data(i)));

            m_chunks.add(data);
        }

        return *this;
    }

    /*!
    @brief деструктор
    @detailed освобождает выделеную память из общей кучи
    */
    ~allocator();

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

    const size_type m_size; ///размер блока в куче
};

template <class T, size_type arena_size, size_type size>
allocator<T, arena_size, size>::allocator(const allocator &other) : m_chunks(PointerManager<chunk_t>(other.m_chunks.size)), m_size(other.m_size)
{
    for (decltype(other.m_chunks.pos) i = 0; i < other.m_chunks.pos; ++i)
    {
        chunk_t data;
        data = std::make_pair(std::get<0>(*other.m_chunks.data(i)), (uint8_t*) std::malloc(std::get<0>(*other.m_chunks.data(i))));

        std::memcpy(std::get<1>(data), std::get<1>(*other.m_chunks.data(i)), std::get<0>(*other.m_chunks.data(i)));

        m_chunks.add(data);
    }
}

template <class T, size_type A, size_type S>
allocator<T, A, S>::~allocator()
{
    for (decltype(m_chunks.length()) i = 0; i < m_chunks.length(); ++i)
    {
        std::free(std::get<1>(*m_chunks.data(i)));
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
        else
        {
            std::runtime_error{"deallocate error"};
        }
    }
}

template <class T, size_type A, size_type S>
T* allocator<T, A, S>::allocate(size_type n)
{
    n = n * sizeof (T);
    if (n > m_available)
    {
        chunk_t data = std::make_pair(n * m_size, (uint8_t*) std::malloc(n * m_size));

        if (!data.second)
            std::bad_alloc();

        m_available = std::get<0>(data);

        m_chunks.add(data);
        m_memory = std::get<1>(*m_chunks.data());
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

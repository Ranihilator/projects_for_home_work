#define REBIND
#include "container.h"

#define BOOST_TEST_MODULE allocator_testing

#include  <limits>
#include <chrono>
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(test_suite_main)

using namespace HW_03;

const auto number = 100;        /// Элементов тестирования

/*!
@brief Тест аллокатора
@detail Аллокатор должен выделить память по запрошенному размеру,
если аллокатор не смог выделить память, то появиться исключение std::bad_alloc().
Если память была выделена, аллокатор вернет указатель на область памяти, где можно конструировать объект.
Если аллокатор при освобождение памяти не смог ее освободить, то появиться исключение std::bad_alloc().
Проверяем аллокатор на утечку памяти, пытаемся освободить память и убедиться что счетчик @ALLOCATOR::alloc_counter@ не изменился
*/
BOOST_AUTO_TEST_CASE(allocator_test)
{
    decltype(ALLOCATOR::alloc_counter) current_memory_allocate = 0;

    /// Проверяем работу аллокатора, чтобы аллокатор выделели только 1 блок памяти
    /// Выделяем массив, проверем каждый элемент, затем все освобождаем
    current_memory_allocate = ALLOCATOR::alloc_counter;         /// Установка 0 отчета выделенной памяти
    if (1)
    {
        ALLOCATOR::allocator<int, number> data;

        int *ptr[number];
        for (auto i = 0; i < number; ++i)
        {
            BOOST_REQUIRE_NO_THROW(ptr[i] = data.allocate(1));
            BOOST_CHECK(ptr[i]!=nullptr);
        }
        for (auto i = number - 1; i >= 0; --i)
        {
            BOOST_REQUIRE_NO_THROW(data.deallocate(ptr[i], 1));
        }

        /// Попытка уничтожить не валидный указатель
        BOOST_REQUIRE_NO_THROW(data.deallocate(ptr[0], 1));
        BOOST_REQUIRE_NO_THROW(data.deallocate(ptr[12], 1));

        /// Убедимся что, аллокатор выделил только 1 блок
        BOOST_CHECK(current_memory_allocate + 1 == ALLOCATOR::alloc_counter);
    }
    /// Убедимся что, счетчик выделенной памяти равен установке 0.
    BOOST_CHECK(current_memory_allocate == ALLOCATOR::alloc_counter);       /// Проверяем утечку

///-----------------------------------------------------------------------------------------------------------------///

    /// Проверяем работу аллокатора, чтобы аллокатор выделели несколько блоков памяти (расширение)
    /// Выделяем массив, проверем каждый элемент, затем все освобождаем
    current_memory_allocate = ALLOCATOR::alloc_counter;         /// Установка 0 отчета выделенной памяти
    if (1)
    {
        ALLOCATOR::allocator<int, number / 10> data;

        int *ptr[number];
        for (auto i = 0; i < number; ++i)
        {
            BOOST_REQUIRE_NO_THROW(ptr[i] = data.allocate(1));
            BOOST_CHECK(ptr[i]!=nullptr);
        }
        for (auto i = number - 1; i >= 0; --i)
        {
            BOOST_REQUIRE_NO_THROW(data.deallocate(ptr[i], 1));
        }

        /// Попытка уничтожить не валидный указатель
        BOOST_REQUIRE_NO_THROW(data.deallocate(ptr[0], 1));
        BOOST_REQUIRE_NO_THROW(data.deallocate(ptr[12], 1));

        /// Убедимся что, аллокатор выделил больше чем 1 блок
        BOOST_CHECK(current_memory_allocate + 1 < ALLOCATOR::alloc_counter);
    }
    /// Убедимся что, счетчик выделенной памяти равен установке 0.
    BOOST_CHECK(current_memory_allocate == ALLOCATOR::alloc_counter);       /// Проверяем утечку
///-----------------------------------------------------------------------------------------------------------------///


    /// Проверяем работу аллокатора, чтобы аллокатор выделели только 1 блок памяти
    /// Выделяем элемент разного размера, проверяем валидность указателя, освобождаем память
    current_memory_allocate = ALLOCATOR::alloc_counter;         /// Установка 0 отчета выделенной памяти
    if (1)
    {
        ALLOCATOR::allocator<int, number> data;

        for (auto i = 0; i < number; ++i)
        {
            int *ptr=nullptr;

            BOOST_REQUIRE_NO_THROW(ptr = data.allocate(i + 1));
            BOOST_CHECK(ptr!=nullptr);
            BOOST_REQUIRE_NO_THROW(data.deallocate(ptr, i + 1));

            ptr = nullptr;
        }

        /// Убедимся что, аллокатор выделил только 1 блок
        BOOST_CHECK(current_memory_allocate + 1 == ALLOCATOR::alloc_counter);
    }
    /// Убедимся что, счетчик выделенной памяти равен установке 0.
    BOOST_CHECK(current_memory_allocate == ALLOCATOR::alloc_counter);       /// Проверяем утечку

///-----------------------------------------------------------------------------------------------------------------///

    /// Проверяем работу аллокатора, чтобы аллокатор выделели несколько блоков памяти (расширение)
    /// Выделяем элемент разного размера, проверяем валидность указателя, освобождаем память
    current_memory_allocate = ALLOCATOR::alloc_counter;         /// Установка 0 отчета выделенной памяти
    if (1)
    {
        ALLOCATOR::allocator<int, number / 10> data;

        for (auto i = 0; i < number; ++i)
        {
            int *ptr=nullptr;

            BOOST_REQUIRE_NO_THROW(ptr = data.allocate(i + 1));
            BOOST_CHECK(ptr!=nullptr);
            BOOST_REQUIRE_NO_THROW(data.deallocate(ptr, i + 1));

            ptr = nullptr;
        }

        /// Убедимся что, аллокатор выделил только 1 блок, т.к. по самому тесту аллокатор не будет расширяться
        BOOST_CHECK(current_memory_allocate + 1 == ALLOCATOR::alloc_counter);
    }

    /// Убедимся что, счетчик выделенной памяти равен установке 0.
    BOOST_CHECK(current_memory_allocate == ALLOCATOR::alloc_counter);       /// Проверяем утечку

///-----------------------------------------------------------------------------------------------------------------///

    /// Попытаемся выделить недопустимый размер памяти
    current_memory_allocate = ALLOCATOR::alloc_counter;/// Установка 0 отчета выделенной памяти
    if (1)
    {
        ALLOCATOR::allocator<int, number / 10> data;

        BOOST_REQUIRE_THROW(data.allocate(0), std::bad_alloc);

        BOOST_REQUIRE_THROW(data.allocate(std::numeric_limits<uint64_t>::max()), std::bad_alloc);
        BOOST_REQUIRE_THROW(data.allocate(std::numeric_limits<uint64_t>::max()-1), std::bad_alloc);

        BOOST_REQUIRE_THROW(data.allocate(std::numeric_limits<int>::max()), std::bad_alloc);
        BOOST_REQUIRE_THROW(data.allocate(std::numeric_limits<int>::max()-1), std::bad_alloc);

        BOOST_REQUIRE_THROW(data.allocate(std::numeric_limits<int>::max()/2), std::bad_alloc);
        BOOST_REQUIRE_THROW(data.allocate(std::numeric_limits<int>::max()/2 + 1), std::bad_alloc);
        BOOST_REQUIRE_THROW(data.allocate(std::numeric_limits<int>::max()/2 - 1), std::bad_alloc);

        BOOST_REQUIRE_THROW(data.allocate(-1), std::bad_alloc);
        BOOST_REQUIRE_THROW(data.allocate(std::numeric_limits<int>::min()), std::bad_alloc);
        BOOST_REQUIRE_THROW(data.allocate(std::numeric_limits<long>::min()), std::bad_alloc);
    }

    /// Убедимся что, счетчик выделенной памяти равен установке 0.
    BOOST_CHECK(current_memory_allocate == ALLOCATOR::alloc_counter);       /// Проверяем утечку

///-----------------------------------------------------------------------------------------------------------------///

    /// Попытаемся скопировать аллокаторы, и убедимся что утечка отсутствует,
    /// также аллокаторы не будут освобождать память, т.к. это должно произойдет в деструкторе аллокатора
    current_memory_allocate = ALLOCATOR::alloc_counter;/// Установка 0 отчета выделенной памяти
    if (1)
    {
        ALLOCATOR::allocator<int, number / 10> data;

        ALLOCATOR::allocator<int, number / 10> data_copy;

        for (auto i = 0; i < number; ++i)
        {
            BOOST_REQUIRE_NO_THROW(data.allocate(1));
        }

        data_copy = data;
    }
    /// Убедимся что, счетчик выделенной памяти равен установке 0.
    BOOST_CHECK(current_memory_allocate == ALLOCATOR::alloc_counter);       /// Проверяем утечку
}

/*!
@brief Тест аллокатора на скорость работы
@detail Сравним скорость аллокатора и стандартного @std::allocator@
*/
BOOST_AUTO_TEST_CASE(allocator_speed)
{
    uint64_t time_result;

///-----------------------------------------------------------------------------------------------------------------///

    /// Выделяем элемент разного размера, проверяем валидность указателя, освобождаем память
    /// Тест скорости стандартного аллокатора @std::allocator@
    if (1)
    {
        auto StartTime = std::chrono::high_resolution_clock::now();
        std::allocator<int>             data;
        for (auto i = 0; i < number; ++i)
        {
            int *ptr=nullptr;

            BOOST_REQUIRE_NO_THROW(ptr = data.allocate(i));
            BOOST_REQUIRE_NO_THROW(data.deallocate(ptr, i));
        }
        auto FinishTime = std::chrono::high_resolution_clock::now();

        auto time = FinishTime - StartTime;
        time_result = std::chrono::duration_cast<std::chrono::microseconds>(time).count();
    }
    std::cout << "std::allocator new delete                          " << time_result << " us" << std::endl;

///-----------------------------------------------------------------------------------------------------------------///

    /// Выделяем элемент разного размера, проверяем валидность указателя, освобождаем память
    /// Тест скорости аллокатора, настройки на @number@ / 10 элементов, аллокатор будет расширяться
    if (1)
    {
        auto StartTime = std::chrono::high_resolution_clock::now();
        ALLOCATOR::allocator<int, number / 10>             data;
        for (auto i = 0; i < number; ++i)
        {
            int *ptr=nullptr;

            BOOST_REQUIRE_NO_THROW(ptr = data.allocate(i + 1));
            BOOST_REQUIRE_NO_THROW(data.deallocate(ptr, i + 1));
        }
        auto FinishTime = std::chrono::high_resolution_clock::now();

        auto time = FinishTime - StartTime;
        time_result = std::chrono::duration_cast<std::chrono::microseconds>(time).count();
    }
    std::cout << "ALLOCATOR::allocator new delete (extending)        " << time_result << " us" << std::endl;

///-----------------------------------------------------------------------------------------------------------------///

    /// Выделяем элемент разного размера, проверяем валидность указателя, освобождаем память
    /// Тест скорости аллокатора, настройки на @number@ элементов, аллокатор не будет расширяться, будет выделен заранее блок на все элементы
    if (1)
    {
        auto StartTime = std::chrono::high_resolution_clock::now();
        ALLOCATOR::allocator<int, number>             data;
        for (auto i = 0; i < number; ++i)
        {
            int *ptr=nullptr;

            BOOST_REQUIRE_NO_THROW(ptr = data.allocate(i + 1));
            BOOST_REQUIRE_NO_THROW(data.deallocate(ptr, i + 1));
        }
        auto FinishTime = std::chrono::high_resolution_clock::now();

        auto time = FinishTime - StartTime;
        time_result = std::chrono::duration_cast<std::chrono::microseconds>(time).count();
    }
    std::cout << "ALLOCATOR::allocator new delete (one allocate)     " << time_result << " us" << std::endl;

///-----------------------------------------------------------------------------------------------------------------///
    std::cout << std::endl;
///-----------------------------------------------------------------------------------------------------------------///

    /// Выделяем массив, проверем каждый элемент, затем все освобождаем
    /// Тест скорости стандартного аллокатора @std::allocator@
    if (1)
    {
        auto StartTime = std::chrono::high_resolution_clock::now();
        std::allocator<int> data;

        int *ptr[number];
        for (auto i = 0; i < number; ++i)
        {
            BOOST_REQUIRE_NO_THROW(ptr[i] = data.allocate(1));
            BOOST_CHECK(ptr[i]!=nullptr);
        }
        for (auto i = number - 1; i >= 0; --i)
        {
            BOOST_REQUIRE_NO_THROW(data.deallocate(ptr[i], 1));
        }

        auto FinishTime = std::chrono::high_resolution_clock::now();

        auto time = FinishTime - StartTime;
        time_result = std::chrono::duration_cast<std::chrono::microseconds>(time).count();
    }
    std::cout << "std::allocator new[] delete[]                      " << time_result << " us" << std::endl;

///-----------------------------------------------------------------------------------------------------------------///

    /// Выделяем массив, проверем каждый элемент, затем все освобождаем
    /// Тест скорости аллокатора, настройка на @number@ / 10 элементов, аллокатор будет расширяться
    if (1)
    {
        auto StartTime = std::chrono::high_resolution_clock::now();
        ALLOCATOR::allocator<int, number / 10> data;

        int *ptr[number];
        for (auto i = 0; i < number; ++i)
        {
            BOOST_REQUIRE_NO_THROW(ptr[i] = data.allocate(1));
            BOOST_CHECK(ptr[i]!=nullptr);
        }
        for (auto i = number - 1; i >= 0; --i)
        {
            BOOST_REQUIRE_NO_THROW(data.deallocate(ptr[i], 1));
        }

        auto FinishTime = std::chrono::high_resolution_clock::now();

        auto time = FinishTime - StartTime;
        time_result = std::chrono::duration_cast<std::chrono::microseconds>(time).count();
    }
    std::cout << "ALLOCATOR::allocator new[] delete[] (extending)    " << time_result << " us" << std::endl;

///-----------------------------------------------------------------------------------------------------------------///

    /// Выделяем массив, проверем каждый элемент, затем все освобождаем
    /// Тест скорости аллокатора, настройка на @number@ элементов, аллокатор не будет расширяться
    if (1)
    {
        auto StartTime = std::chrono::high_resolution_clock::now();
        ALLOCATOR::allocator<int, number> data;

        int *ptr[number];
        for (auto i = 0; i < number; ++i)
        {
            BOOST_REQUIRE_NO_THROW(ptr[i] = data.allocate(1));
            BOOST_CHECK(ptr[i]!=nullptr);
        }
        for (auto i = number - 1; i >= 0; --i)
        {
            BOOST_REQUIRE_NO_THROW(data.deallocate(ptr[i], 1));
        }

        auto FinishTime = std::chrono::high_resolution_clock::now();

        auto time = FinishTime - StartTime;
        time_result = std::chrono::duration_cast<std::chrono::microseconds>(time).count();
    }
    std::cout << "ALLOCATOR::allocator new[] delete[] (one allocate) " << time_result << " us" << std::endl;

    return;
}

BOOST_AUTO_TEST_SUITE_END()

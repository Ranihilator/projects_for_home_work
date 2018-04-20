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
\brief Тест контейнера
\details Проверка работоспособности контейнера с 2х-мя аллокаторами
*/
BOOST_AUTO_TEST_CASE(container_test)
{
	decltype(ALLOCATOR::alloc_counter) current_memory_allocate = 0;

	/// Проверяем работу контейнера, со стандартным аллокатором std::allocator
	current_memory_allocate = ALLOCATOR::alloc_counter;         /// Установка 0 отчета выделенной памяти
	if (1)
	{
		CONTAINER::container<int> data;

		BOOST_CHECK(data.empty());///Контейнер должен быть пустым

		for (auto i = 0; i < number; ++i)
			data.push_back(i);

		BOOST_CHECK(!data.empty());               /// В Контейнер должены быть элементы
		BOOST_CHECK(data.size() == number);       /// Проверяем кол-во элементов

		/// Проверяем целостность элементов
		for (auto i = 0 ; i < data.size(); ++i)
		{
			auto val = 0;
			BOOST_CHECK_NO_THROW(val = data.at(i));
			BOOST_CHECK(val == i);
		}

		data.pop_back();

		BOOST_CHECK(!data.empty());                 /// В Контейнер должены быть элементы
		BOOST_CHECK(data.size() == number - 1);     /// Проверяем кол-во элементов

		/// Проверяем целостность элементов после удаления
		for (auto i = 0 ; i < data.size(); ++i)
		{
			auto val = 0;
			BOOST_CHECK_NO_THROW(val = data.at(i));
			BOOST_CHECK(val == i);
		}

		data.clear();                   /// Удалить содержимое контейнера
		BOOST_CHECK(data.empty());      /// Контейнер должен быть пустым

	}
	/// Убедимся что, счетчик выделенной памяти равен установке 0.
	BOOST_CHECK(current_memory_allocate == ALLOCATOR::alloc_counter);       /// Проверяем утечку

///-----------------------------------------------------------------------------------------------------------------///

	/// Проверяем работу контейнера, с аллокатором
	/// Аллокатор выделит память 1 раз
	current_memory_allocate = ALLOCATOR::alloc_counter;         /// Установка 0 отчета выделенной памяти
	if (1)
	{
		CONTAINER::container<int, ALLOCATOR::allocator<int, number>> data;

		BOOST_CHECK(data.empty());///Контейнер должен быть пустым

		for (auto i = 0; i < number; ++i)
			data.push_back(i);

		BOOST_CHECK(!data.empty());               /// В Контейнер должены быть элементы
		BOOST_CHECK(data.size() == number);       /// Проверяем кол-во элементов

		/// Проверяем целостность элементов
		for (auto i = 0 ; i < data.size(); ++i)
		{
			auto val = 0;
			BOOST_CHECK_NO_THROW(val = data.at(i));
			BOOST_CHECK(val == i);
		}

		data.pop_back();

		BOOST_CHECK(!data.empty());                 /// В Контейнер должены быть элементы
		BOOST_CHECK(data.size() == number - 1);     /// Проверяем кол-во элементов

		/// Проверяем целостность элементов после удаления
		for (auto i = 0 ; i < data.size(); ++i)
		{
			auto val = 0;
			BOOST_CHECK_NO_THROW(val = data.at(i));
			BOOST_CHECK(val == i);
		}

		data.clear();                   /// Удалить содержимое контейнера
		BOOST_CHECK(data.empty());      /// Контейнер должен быть пустым

		/// Убедимся что, аллокатор контейнера выделил только 1 блок
		BOOST_CHECK(current_memory_allocate + 1 == ALLOCATOR::alloc_counter);
	}
	/// Убедимся что, счетчик выделенной памяти равен установке 0.
	BOOST_CHECK(current_memory_allocate == ALLOCATOR::alloc_counter);       /// Проверяем утечку

///-----------------------------------------------------------------------------------------------------------------///

	/// Проверяем работу контейнера, с аллокатором
	/// Аллокатор будет расширяться
	current_memory_allocate = ALLOCATOR::alloc_counter;         /// Установка 0 отчета выделенной памяти
	if (1)
	{
		CONTAINER::container < int, ALLOCATOR::allocator < int, number / 10 >> data;

		BOOST_CHECK(data.empty());///Контейнер должен быть пустым

		for (auto i = 0; i < number; ++i)
			data.push_back(i);

		BOOST_CHECK(!data.empty());               /// В Контейнер должены быть элементы
		BOOST_CHECK(data.size() == number);       /// Проверяем кол-во элементов

		/// Проверяем целостность элементов
		for (auto i = 0 ; i < data.size(); ++i)
		{
			auto val = 0;
			BOOST_CHECK_NO_THROW(val = data.at(i));
			BOOST_CHECK(val == i);
		}

		data.pop_back();

		BOOST_CHECK(!data.empty());                 /// В Контейнер должены быть элементы
		BOOST_CHECK(data.size() == number - 1);     /// Проверяем кол-во элементов

		/// Проверяем целостность элементов после удаления
		for (auto i = 0 ; i < data.size(); ++i)
		{
			auto val = 0;
			BOOST_CHECK_NO_THROW(val = data.at(i));
			BOOST_CHECK(val == i);
		}

		data.clear();                   /// Удалить содержимое контейнера
		BOOST_CHECK(data.empty());      /// Контейнер должен быть пустым

		/// Убедимся что, аллокатор контейнера выделил больше чем 1 блок
		BOOST_CHECK(current_memory_allocate + 1 < ALLOCATOR::alloc_counter);
	}
	/// Убедимся что, счетчик выделенной памяти равен установке 0.
	BOOST_CHECK(current_memory_allocate == ALLOCATOR::alloc_counter);       /// Проверяем утечку
}

/*!
\brief Тест контейнера на скорость работы
*/
BOOST_AUTO_TEST_CASE(container_speed)
{
	uint64_t time_result;

	/// Замеряем время работы контейнера со стандартным аллокатором std::allocator
	if (1)
	{
		auto StartTime = std::chrono::high_resolution_clock::now();
		CONTAINER::container<int> data;

		for (auto i = 0; i < number; ++i)
			data.push_back(i);

		data.clear();

		auto FinishTime = std::chrono::high_resolution_clock::now();

		auto time = FinishTime - StartTime;
		time_result = std::chrono::duration_cast<std::chrono::microseconds>(time).count();
	}
	std::cout << "std::allocator                      " << time_result << " us" << std::endl;

///-----------------------------------------------------------------------------------------------------------------///

	/// Замеряем время работы контейнера с кол-во элементов number
	/// Контейнер выделит память 1 раз
	if (1)
	{
		auto StartTime = std::chrono::high_resolution_clock::now();
		CONTAINER::container<int, ALLOCATOR::allocator<int, number>> data;

		for (auto i = 0; i < number; ++i)
			data.push_back(i);

		data.clear();

		auto FinishTime = std::chrono::high_resolution_clock::now();

		auto time = FinishTime - StartTime;
		time_result = std::chrono::duration_cast<std::chrono::microseconds>(time).count();
	}
	std::cout << "ALLOCATOR::allocator (one allocate) " << time_result << " us" << std::endl;

	///-----------------------------------------------------------------------------------------------------------------///

	/// Замеряем время работы контейнера с кол-во элементов number / 10
	/// Контейнер будет расширяться
	if (1)
	{
		auto StartTime = std::chrono::high_resolution_clock::now();
		CONTAINER::container < int, ALLOCATOR::allocator < int, number / 10 >> data;

		for (auto i = 0; i < number; ++i)
			data.push_back(i);

		data.clear();

		auto FinishTime = std::chrono::high_resolution_clock::now();

		auto time = FinishTime - StartTime;
		time_result = std::chrono::duration_cast<std::chrono::microseconds>(time).count();
	}
	std::cout << "ALLOCATOR::allocator (extending)    " << time_result << " us" << std::endl;
}

BOOST_AUTO_TEST_SUITE_END()



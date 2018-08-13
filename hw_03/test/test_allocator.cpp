/*!
\file
\brief test allocator
*/

#define REBIND
#include "container.h"

#define BOOST_TEST_MODULE allocator_testing

#include  <limits>
#include <chrono>
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(test_suite_main)

using namespace HW_03;

const auto number = 100;        ///< elements of test

/*!
\brief allocator test
\details allocator must be allocate memory by request size,
if allocator can't allocate memory, then std::bad_alloc will be throw
if memory will be allocate, allocator will return pointer in memory poll, where object's can be construct.
if allocator try to free memory and it can't free, then std::bad_alloc will be throw.
Check allocator for memory leak, try to free memory and checking what ALLOCATOR::alloc_counter not changed.


*/
BOOST_AUTO_TEST_CASE(allocator_test)
{
	decltype(ALLOCATOR::alloc_counter) current_memory_allocate = 0;

    /// Check allocator work, allocator must be allocate 1 block memory
    /// allocate array, then check each elements, then all free
    /// \code
	current_memory_allocate = ALLOCATOR::alloc_counter; 
	if (1)
	{
		ALLOCATOR::allocator<int, number> data;

		int *ptr[number];
		for (auto i = 0; i < number; ++i)
		{
			BOOST_REQUIRE_NO_THROW(ptr[i] = data.allocate(1));
			BOOST_CHECK(ptr[i] != nullptr);
		}
		for (auto i = number - 1; i >= 0; --i)
			BOOST_REQUIRE_NO_THROW(data.deallocate(ptr[i], 1));

		BOOST_REQUIRE_NO_THROW(data.deallocate(ptr[0], 1));
		BOOST_REQUIRE_NO_THROW(data.deallocate(ptr[12], 1));

		BOOST_CHECK(current_memory_allocate + 1 == ALLOCATOR::alloc_counter);
	}
	BOOST_CHECK(current_memory_allocate == ALLOCATOR::alloc_counter);
	/// \endcode

    /// Check allocator work, allocator must be allocate several block memory (extending allocator)
    /// allocate array, then check each elements, then all free
    /// \code
	current_memory_allocate = ALLOCATOR::alloc_counter;
	if (1)
	{
		ALLOCATOR::allocator < int, number / 10 > data;

		int *ptr[number];
		for (auto i = 0; i < number; ++i)
		{
			BOOST_REQUIRE_NO_THROW(ptr[i] = data.allocate(1));
			BOOST_CHECK(ptr[i] != nullptr);
		}
		for (auto i = number - 1; i >= 0; --i)
			BOOST_REQUIRE_NO_THROW(data.deallocate(ptr[i], 1));

		BOOST_REQUIRE_NO_THROW(data.deallocate(ptr[0], 1));
		BOOST_REQUIRE_NO_THROW(data.deallocate(ptr[12], 1));

		BOOST_CHECK(current_memory_allocate + 1 < ALLOCATOR::alloc_counter);
	}
	BOOST_CHECK(current_memory_allocate == ALLOCATOR::alloc_counter);
    /// \endcode

    /// Check allocator work, allocator must be allocate 1 block memory
    /// Allocate element various size, check valid pointer, free memory
    /// \code
	current_memory_allocate = ALLOCATOR::alloc_counter;
	if (1)
	{
		ALLOCATOR::allocator<int, number> data;

		for (auto i = 0; i < number; ++i)
		{
			int *ptr = nullptr;

			BOOST_REQUIRE_NO_THROW(ptr = data.allocate(i + 1));
			BOOST_CHECK(ptr != nullptr);
			BOOST_REQUIRE_NO_THROW(data.deallocate(ptr, i + 1));

			ptr = nullptr;
		}

		BOOST_CHECK(current_memory_allocate + 1 == ALLOCATOR::alloc_counter);
	}
	BOOST_CHECK(current_memory_allocate == ALLOCATOR::alloc_counter);
	/// \endcode

	
    /// Check allocator work, allocator must be allocate several block memory (extending allocator)
    /// Allocate element various size, check valid pointer, free memory
    /// \code
	current_memory_allocate = ALLOCATOR::alloc_counter;
	if (1)
	{
		ALLOCATOR::allocator < int, number / 10 > data;

		for (auto i = 0; i < number; ++i)
		{
			int *ptr = nullptr;

			BOOST_REQUIRE_NO_THROW(ptr = data.allocate(i + 1));
			BOOST_CHECK(ptr != nullptr);
			BOOST_REQUIRE_NO_THROW(data.deallocate(ptr, i + 1));

			ptr = nullptr;
		}

		BOOST_CHECK(current_memory_allocate + 1 == ALLOCATOR::alloc_counter);
	}

	BOOST_CHECK(current_memory_allocate == ALLOCATOR::alloc_counter);
	/// \endcode

    /// \code
    /// Try to allocate invalid size of memory
	current_memory_allocate = ALLOCATOR::alloc_counter;
	if (1)
	{
		ALLOCATOR::allocator < int, number / 10 > data;

		BOOST_REQUIRE_THROW(data.allocate(0), std::bad_alloc);

		BOOST_REQUIRE_THROW(data.allocate(std::numeric_limits<uint64_t>::max()), std::bad_alloc);
		BOOST_REQUIRE_THROW(data.allocate(std::numeric_limits<uint64_t>::max() - 1), std::bad_alloc);

		BOOST_REQUIRE_THROW(data.allocate(std::numeric_limits<int>::max()), std::bad_alloc);
		BOOST_REQUIRE_THROW(data.allocate(std::numeric_limits<int>::max() - 1), std::bad_alloc);

		BOOST_REQUIRE_THROW(data.allocate(std::numeric_limits<int>::max() / 2), std::bad_alloc);
		BOOST_REQUIRE_THROW(data.allocate(std::numeric_limits<int>::max() / 2 + 1), std::bad_alloc);
		BOOST_REQUIRE_THROW(data.allocate(std::numeric_limits<int>::max() / 2 - 1), std::bad_alloc);

		BOOST_REQUIRE_THROW(data.allocate(-1), std::bad_alloc);
		BOOST_REQUIRE_THROW(data.allocate(std::numeric_limits<int>::min()), std::bad_alloc);
		BOOST_REQUIRE_THROW(data.allocate(std::numeric_limits<long>::min()), std::bad_alloc);
	}

	BOOST_CHECK(current_memory_allocate == ALLOCATOR::alloc_counter);
	/// \endcode

	/// Try to copy allocator, and checked leak memory is absent.
	/// allocator will not free memory, etc. must be done in destructor
    /// \code
	current_memory_allocate = ALLOCATOR::alloc_counter;/// Установка 0 отчета выделенной памяти
	if (1)
	{
		ALLOCATOR::allocator < int, number / 10 > data;

		ALLOCATOR::allocator < int, number / 10 > data_copy;

		for (auto i = 0; i < number; ++i)
			BOOST_REQUIRE_NO_THROW(data.allocate(1));

		data_copy = data;
	}
	BOOST_CHECK(current_memory_allocate == ALLOCATOR::alloc_counter);
	/// \endcode
}

/*!
\see ALLOCATOR::allocator
\brief Allocator test in speed
\details try to meassure speed std::allocator and ALLOCATOR::allocator
*/
BOOST_AUTO_TEST_CASE(allocator_speed)
{
	uint64_t time_result;

    /// Allocate element various size, check valid pointer, free memory
	/// Speed test std::allocator
    /// \code
	if (1)
	{
		auto StartTime = std::chrono::high_resolution_clock::now();
		std::allocator<int>             data;
		for (auto i = 0; i < number; ++i)
		{
			int *ptr = nullptr;

			BOOST_REQUIRE_NO_THROW(ptr = data.allocate(i));
			BOOST_REQUIRE_NO_THROW(data.deallocate(ptr, i));
		}
		auto FinishTime = std::chrono::high_resolution_clock::now();

		auto time = FinishTime - StartTime;
		time_result = std::chrono::duration_cast<std::chrono::microseconds>(time).count();
	}
	std::cout << "std::allocator new delete                          " << time_result << " us" << std::endl;
    /// \endcode

    /// Allocate element various size, check valid pointer, free memory
	/// Speed test ALLOCATOR::allocator when allocator is extending
    /// \code
	if (1)
	{
		auto StartTime = std::chrono::high_resolution_clock::now();
		ALLOCATOR::allocator < int, number / 10 >             data;
		for (auto i = 0; i < number; ++i)
		{
			int *ptr = nullptr;

			BOOST_REQUIRE_NO_THROW(ptr = data.allocate(i + 1));
			BOOST_REQUIRE_NO_THROW(data.deallocate(ptr, i + 1));
		}
		auto FinishTime = std::chrono::high_resolution_clock::now();

		auto time = FinishTime - StartTime;
		time_result = std::chrono::duration_cast<std::chrono::microseconds>(time).count();
	}
	std::cout << "ALLOCATOR::allocator new delete (extending)        " << time_result << " us" << std::endl;
    /// \endcode

    /// Allocate element various size, check valid pointer, free memory
	/// Speed test ALLOCATOR::allocator when allocator is allocate const block size
    /// \code
	if (1)
	{
		auto StartTime = std::chrono::high_resolution_clock::now();
		ALLOCATOR::allocator<int, number>             data;
		for (auto i = 0; i < number; ++i)
		{
			int *ptr = nullptr;

			BOOST_REQUIRE_NO_THROW(ptr = data.allocate(i + 1));
			BOOST_REQUIRE_NO_THROW(data.deallocate(ptr, i + 1));
		}
		auto FinishTime = std::chrono::high_resolution_clock::now();

		auto time = FinishTime - StartTime;
		time_result = std::chrono::duration_cast<std::chrono::microseconds>(time).count();
	}
	std::cout << "ALLOCATOR::allocator new delete (one allocate)     " << time_result << " us" << std::endl;
    /// \endcode

	std::cout << std::endl;

    /// Allocate array, check all elements, when freeing
	/// Speed test std::allocator
    /// \code
	if (1)
	{
		auto StartTime = std::chrono::high_resolution_clock::now();
		std::allocator<int> data;

		int *ptr[number];
		for (auto i = 0; i < number; ++i)
		{
			BOOST_REQUIRE_NO_THROW(ptr[i] = data.allocate(1));
			BOOST_CHECK(ptr[i] != nullptr);
		}
		for (auto i = number - 1; i >= 0; --i)
			BOOST_REQUIRE_NO_THROW(data.deallocate(ptr[i], 1));

		auto FinishTime = std::chrono::high_resolution_clock::now();

		auto time = FinishTime - StartTime;
		time_result = std::chrono::duration_cast<std::chrono::microseconds>(time).count();
	}
	std::cout << "std::allocator new[] delete[]                      " << time_result << " us" << std::endl;
    /// \endcode

    /// Allocate array, check all elements, when freeing
	/// Speed test std::allocator when allocator is extending
    /// \code
	if (1)
	{
		auto StartTime = std::chrono::high_resolution_clock::now();
		ALLOCATOR::allocator < int, number / 10 > data;

		int *ptr[number];
		for (auto i = 0; i < number; ++i)
		{
			BOOST_REQUIRE_NO_THROW(ptr[i] = data.allocate(1));
			BOOST_CHECK(ptr[i] != nullptr);
		}
		for (auto i = number - 1; i >= 0; --i)
			BOOST_REQUIRE_NO_THROW(data.deallocate(ptr[i], 1));

		auto FinishTime = std::chrono::high_resolution_clock::now();

		auto time = FinishTime - StartTime;
		time_result = std::chrono::duration_cast<std::chrono::microseconds>(time).count();
	}
	std::cout << "ALLOCATOR::allocator new[] delete[] (extending)    " << time_result << " us" << std::endl;
    /// \endcode

    /// Allocate array, check all elements, when freeing
    /// Speed test std::allocator when allocator is allocate const size block
    /// \code
	if (1)
	{
		auto StartTime = std::chrono::high_resolution_clock::now();
		ALLOCATOR::allocator<int, number> data;

		int *ptr[number];
		for (auto i = 0; i < number; ++i)
		{
			BOOST_REQUIRE_NO_THROW(ptr[i] = data.allocate(1));
			BOOST_CHECK(ptr[i] != nullptr);
		}
		for (auto i = number - 1; i >= 0; --i)
			BOOST_REQUIRE_NO_THROW(data.deallocate(ptr[i], 1));

		auto FinishTime = std::chrono::high_resolution_clock::now();

		auto time = FinishTime - StartTime;
		time_result = std::chrono::duration_cast<std::chrono::microseconds>(time).count();
	}
	std::cout << "ALLOCATOR::allocator new[] delete[] (one allocate) " << time_result << " us" << std::endl;
    /// \endcode
	return;
}

BOOST_AUTO_TEST_SUITE_END()

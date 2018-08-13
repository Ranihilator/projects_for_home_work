/*!
\file
\brief test container
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
\brief Container test
\details Check 2x containers
*/
BOOST_AUTO_TEST_CASE(container_test)
{
	decltype(ALLOCATOR::alloc_counter) current_memory_allocate = 0;

    /// Check container with std::allocator
    /// \code
	current_memory_allocate = ALLOCATOR::alloc_counter;
	if (1)
	{
		CONTAINER::container<int> data;

		BOOST_CHECK(data.empty());

		for (auto i = 0; i < number; ++i)
			data.push_back(i);

		BOOST_CHECK(!data.empty());
		BOOST_CHECK(data.size() == number);

		for (auto i = 0 ; i < data.size(); ++i)
		{
			auto val = 0;
			BOOST_CHECK_NO_THROW(val = data.at(i));
			BOOST_CHECK(val == i);
		}

		data.pop_back();

		BOOST_CHECK(!data.empty());
		BOOST_CHECK(data.size() == number - 1);

		for (auto i = 0 ; i < data.size(); ++i)
		{
			auto val = 0;
			BOOST_CHECK_NO_THROW(val = data.at(i));
			BOOST_CHECK(val == i);
		}

		data.clear();
		BOOST_CHECK(data.empty());
	}
	BOOST_CHECK(current_memory_allocate == ALLOCATOR::alloc_counter);
    /// \endcode

    /// Check container with ALLOCATOR::allocator
    /// Allocator must be allocate memory 1 times
    /// \code
	current_memory_allocate = ALLOCATOR::alloc_counter;
	if (1)
	{
		CONTAINER::container<int, ALLOCATOR::allocator<int, number>> data;

		BOOST_CHECK(data.empty());

		for (auto i = 0; i < number; ++i)
			data.push_back(i);

		BOOST_CHECK(!data.empty());
		BOOST_CHECK(data.size() == number);

		for (auto i = 0 ; i < data.size(); ++i)
		{
			auto val = 0;
			BOOST_CHECK_NO_THROW(val = data.at(i));
			BOOST_CHECK(val == i);
		}

		data.pop_back();

		BOOST_CHECK(!data.empty());
		BOOST_CHECK(data.size() == number - 1);

		for (auto i = 0 ; i < data.size(); ++i)
		{
			auto val = 0;
			BOOST_CHECK_NO_THROW(val = data.at(i));
			BOOST_CHECK(val == i);
		}

		data.clear();
		BOOST_CHECK(data.empty());

		BOOST_CHECK(current_memory_allocate + 1 == ALLOCATOR::alloc_counter);
	}
	BOOST_CHECK(current_memory_allocate == ALLOCATOR::alloc_counter);
	/// \endcode

    /// Check container with ALLOCATOR::allocator
    /// Allocator will be extending
    /// \code
	current_memory_allocate = ALLOCATOR::alloc_counter;
	if (1)
	{
		CONTAINER::container < int, ALLOCATOR::allocator < int, number / 10 >> data;

		BOOST_CHECK(data.empty());

		for (auto i = 0; i < number; ++i)
			data.push_back(i);

		BOOST_CHECK(!data.empty());
		BOOST_CHECK(data.size() == number);

		for (auto i = 0 ; i < data.size(); ++i)
		{
			auto val = 0;
			BOOST_CHECK_NO_THROW(val = data.at(i));
			BOOST_CHECK(val == i);
		}

		data.pop_back();

		BOOST_CHECK(!data.empty());
		BOOST_CHECK(data.size() == number - 1);

		for (auto i = 0 ; i < data.size(); ++i)
		{
			auto val = 0;
			BOOST_CHECK_NO_THROW(val = data.at(i));
			BOOST_CHECK(val == i);
		}

		data.clear();
		BOOST_CHECK(data.empty());

		BOOST_CHECK(current_memory_allocate + 1 < ALLOCATOR::alloc_counter);
	}
	BOOST_CHECK(current_memory_allocate == ALLOCATOR::alloc_counter);
	/// \endcode
}

/*!
\brief Speed test container
*/
BOOST_AUTO_TEST_CASE(container_speed)
{
	uint64_t time_result;

	/// std::allocator speed test with container
    /// \code
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
    /// \endcode

	/// ALLOCATOR::allocator speed test with container
    /// Container must be allocatate block of data 1 times
    /// \code
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
	/// \endcode

	/// ALLOCATOR::allocator speed test with container when element allocate in 1 block
	/// Container will be extending
    /// \code
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
    /// \endcode
}

BOOST_AUTO_TEST_SUITE_END()



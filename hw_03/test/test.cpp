#include "main.h"

#include <deque>
#include <random>
#include <ctime>
#include <algorithm>

#define BOOST_TEST_MODULE allocator_test

#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(test_suite_main)

/*!
@brief Тест аллокатора
*/
BOOST_AUTO_TEST_CASE(allocator_test)
{
	ALLOCATOR::allocator<int, 1, 10> data;

	int *ptr=nullptr;

	for (auto i = 1; i < 100; ++i)
	{
		BOOST_REQUIRE_NO_THROW(ptr = data.allocate(i));
		BOOST_REQUIRE_NO_THROW(data.deallocate(ptr, i));

		ptr = nullptr;
	}
}

/*!
@brief Тест контейнера со стандартным аллокатором и разработанным
*/
BOOST_AUTO_TEST_CASE(container_test)
{
    std::deque <int> model;

    std::deque <int> test_data;
    std::deque <int> test_data_alloc;;

	CONTAINER::container<int> data;
	CONTAINER::container<int, ALLOCATOR::allocator<int>> data_alloc;

	for (auto i = 0; i < 100; ++i)
	{
        int val = 0;

        std::generate_n(&val, 1, std::rand);

		data.push_back(val);
		data_alloc.push_back(val);
		model.push_back(val);
	}

	for (auto i = 0; i < 100; ++i)
	{
		test_data.push_back(data[i]);
		test_data_alloc.push_back(data_alloc[i]);
	}

    BOOST_CHECK(model==test_data);
    BOOST_CHECK(model==test_data_alloc);
}

/*!
@brief Тест контейнера и аллокатора для проверки целостности данных для выполнения ДЗ
*/
BOOST_AUTO_TEST_CASE(task_test)
{
    std::deque <int> model;
    std::deque <int> test;

	std::map<int, int, std::less<int>, ALLOCATOR::allocator<std::pair<int, int>, 1,10>> data_map;
	CONTAINER::container<int> data_container;
	CONTAINER::container<int, ALLOCATOR::allocator<int, 1, 10>> data_container_alloc;

    for (auto i = 0; i < 100; ++i)
	{
        int val = 0;

        std::generate_n(&val, 1, std::rand);

		data_map[i] = val;
		data_container.push_back(val);
		data_container_alloc.push_back(val);
		model.push_back(val);
	}

	for (auto i = 0; i < 100; ++i)
	{
        test.push_back(data_map[i]);
	}
    BOOST_CHECK(model==test);
    test.clear();

	for (auto i = 0; i < 100; ++i)
	{
        test.push_back(data_container[i]);
	}
    BOOST_CHECK(model==test);
    test.clear();

	for (auto i = 0; i < 100; ++i)
	{
        test.push_back(data_container_alloc[i]);
	}
    BOOST_CHECK(model==test);
    test.clear();
}

BOOST_AUTO_TEST_SUITE_END()

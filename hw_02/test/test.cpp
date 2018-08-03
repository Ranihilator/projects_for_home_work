/*!
\file
\brief Test ip address sort and filtering
*/

#include "filter.h"
#include <random>
#include <ctime>
#include <sstream>
#define BOOST_TEST_MODULE test_filter

#include <boost/test/unit_test.hpp>

using namespace HW_02::FILTER;

BOOST_AUTO_TEST_SUITE(test_suite_main)

BOOST_AUTO_TEST_CASE(split_ip_test)
{
	std::regex ip_filter (FILTER_REGEX);

	/// Checking that split ip throw std::invalid_argument if ip address has invalid
	/// \code
	BOOST_REQUIRE_THROW(split_ip("", ip_filter), std::invalid_argument);
	BOOST_REQUIRE_THROW(split_ip("fsafsafsafsa", ip_filter), std::invalid_argument);
	BOOST_REQUIRE_THROW(split_ip("1,2,3,4", ip_filter), std::invalid_argument);
	BOOST_REQUIRE_THROW(split_ip("a.b.c.d", ip_filter), std::invalid_argument);
	BOOST_REQUIRE_THROW(split_ip("1.2.3.4a", ip_filter), std::invalid_argument);
	BOOST_REQUIRE_THROW(split_ip("f1.2.3.4", ip_filter), std::invalid_argument);
	BOOST_REQUIRE_THROW(split_ip("1.a2.3.4", ip_filter), std::invalid_argument);
	BOOST_REQUIRE_THROW(split_ip("1.2.s3.4", ip_filter), std::invalid_argument);
	/// \endcode

	/// Split ip test
	/// \code
	BOOST_CHECK(split_ip("0.0.0.0",ip_filter) == std::make_tuple(0,0,0,0));
	BOOST_CHECK(split_ip("1.2.3.4",ip_filter) == std::make_tuple(1,2,3,4));
	BOOST_CHECK(split_ip("255.255.255.255",ip_filter) == std::make_tuple(255,255,255,255));
	BOOST_CHECK(split_ip("7 3 1garbage 127.0.0.25 garbage 1 2 6 1",ip_filter) == std::make_tuple(127,0,0,25));
	BOOST_CHECK(split_ip("1.2.3,5 192.168.0.1 1,2,3,4",ip_filter) == std::make_tuple(192,168,0,1));
	BOOST_CHECK(split_ip("1.2.3.5 192.168.0.1 127.0.0.1",ip_filter) == std::make_tuple(1,2,3,5));
	BOOST_CHECK(split_ip("10.0.0.1 \t \t \t \n 192.168.1.1",ip_filter) == std::make_tuple(10,0,0,1));
	BOOST_CHECK(split_ip("\t \t \t \n 192.168.1.1",ip_filter) == std::make_tuple(192,168,1,1));
	/// \endcode
}

BOOST_AUTO_TEST_CASE(filter_test)
{
	/// Sorting without filtering
	/// \code
	auto data = IP_Address_Sort();
	data << std::make_tuple(0,0,0,0);
	data << std::make_tuple(0,0,0,127);
	data << std::make_tuple(0,0,0,1);
	data << std::make_tuple(255,255,127,255);
	data << std::make_tuple(127,1,1,1);
	data << std::make_tuple(0,0,0,64);
	data << std::make_tuple(0,0,0,254);

	const std::deque<ip_address> model
	{
		{std::make_tuple(255,255,127,255)},
		{std::make_tuple(127,1,1,1)},
		{std::make_tuple(0,0,0,254)},
		{std::make_tuple(0,0,0,127)},
		{std::make_tuple(0,0,0,64)},
		{std::make_tuple(0,0,0,1)},
		{std::make_tuple(0,0,0,0)}
	};

	std::sort(data.rbegin(), data.rend());

	std::deque<ip_address> object;
	for (auto &i : data)
	{
		object.emplace_back(i);
	}

	BOOST_CHECK(model == object);
	/// \endcode

	/// Sorting with filtering
	/// \code
	auto data_s = IP_Address_Sort(-1,-1,-1,1);

	const std::deque<ip_address> model_s
	{
		{std::make_tuple(127,1,1,1)},
		{std::make_tuple(0,0,0,1)},
	};

	data_s << std::make_tuple(0,0,0,0);
	data_s << std::make_tuple(0,0,0,127);
	data_s << std::make_tuple(0,0,0,1);
	data_s << std::make_tuple(255,255,127,255);
	data_s << std::make_tuple(127,1,1,1);
	data_s << std::make_tuple(0,0,0,64);
	data_s << std::make_tuple(0,0,0,254);

	std::sort(data_s.rbegin(), data_s.rend());

	std::deque<ip_address> object_s;
	for (auto &i : data_s)
	{
		object_s.emplace_back(i);
	}

	BOOST_CHECK(model_s == object_s);
	/// \endocde

	/// Sorting with filtering any byte
	/// \code
	auto data_a = IP_Address_Sort_Any(0);

	const std::deque<ip_address> model_a
	{
		{std::make_tuple(0,0,0,254)},
		{std::make_tuple(0,0,0,127)},
		{std::make_tuple(0,0,0,64)},
		{std::make_tuple(0,0,0,1)},
		{std::make_tuple(0,0,0,0)}
	};

	data_a << std::make_tuple(0,0,0,0);
	data_a << std::make_tuple(0,0,0,127);
	data_a << std::make_tuple(0,0,0,1);
	data_a << std::make_tuple(255,255,127,255);
	data_a << std::make_tuple(127,1,1,1);
	data_a << std::make_tuple(0,0,0,64);
	data_a << std::make_tuple(0,0,0,254);

	std::sort(data_a.rbegin(), data_a.rend());

	std::deque<ip_address> object_a;
	for (auto &i : data_a)
	{
		object_a.emplace_back(i);
	}

	BOOST_CHECK(model_a == object_a);
	/// \endocde
}


///Задание №3 Реализовать constexpr функцию bin_id - определения ближайшей большей степени двойки
constexpr uint64_t bin_id(uint64_t x, uint64_t t = 0x8000000000000000, int c = 64)
{
	return (c >= 0) ? ((x <= t) ? (bin_id(x, t >> 1, --c)) : (c)) : (0);
}

BOOST_AUTO_TEST_CASE(external_test)
{
	BOOST_STATIC_ASSERT(bin_id(0) == 0);
	BOOST_STATIC_ASSERT(bin_id(1) == 0);
	BOOST_STATIC_ASSERT(bin_id(2) == 1);
	BOOST_STATIC_ASSERT(bin_id(4) == 2);
	BOOST_STATIC_ASSERT(bin_id(7) == 3);
	BOOST_STATIC_ASSERT(bin_id(8) == 3);
	BOOST_STATIC_ASSERT(bin_id(9) == 4);
	BOOST_STATIC_ASSERT(bin_id(1023) == 10);
	BOOST_STATIC_ASSERT(bin_id(1024) == 10);
	BOOST_STATIC_ASSERT(bin_id(1025) == 11);
	BOOST_STATIC_ASSERT(bin_id(1024 * 1024 - 33) == 20);
	BOOST_STATIC_ASSERT(bin_id(1024 * 1024) == 20);
	BOOST_STATIC_ASSERT(bin_id(1024 * 1024 + 33) == 21);
	BOOST_STATIC_ASSERT(bin_id(1024 * 1024 * 1024 - 127) == 30);
	BOOST_STATIC_ASSERT(bin_id(1024 * 1024 * 1024) == 30);
	BOOST_STATIC_ASSERT(bin_id(1024 * 1024 * 1024 + 127) == 31);
	BOOST_STATIC_ASSERT(bin_id((uint64_t)0x8000000000000000 - 127) == 63);
	BOOST_STATIC_ASSERT(bin_id((uint64_t)0x8000000000000000) == 63);
	BOOST_STATIC_ASSERT(bin_id((uint64_t)0x8000000000000000 + 127) == 64);
	BOOST_STATIC_ASSERT(bin_id((uint64_t)0xFFFFFFFFFFFFFFFF) == 64);
}


BOOST_AUTO_TEST_SUITE_END()


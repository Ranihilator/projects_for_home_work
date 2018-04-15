/*! \file
    \brief Test for print conditional ip address.

    Test print_ip function to represent random integer type
    Test print_ip function to represent string type
    Test print_ip function to represent container type
    Test print_ip function to represent tuple is same type

    \see print_ip()
*/

#define BOOST_TEST_MODULE print_ip_test

#include <boost/test/unit_test.hpp>

#include "print.h"
#include "tuple.h"

/*!
\brief name of test suite
*/
BOOST_AUTO_TEST_SUITE(test_suite_main)

using namespace HW_04::PRINT;

/*!
\brief capture stdout symbol to string buffer
*/
std::string stdout_capture(const std::function<void()>& print_function)
{
	std::stringstream buffer;

	/// start capture stdout to buffer
	/// \code
	std::streambuf * old = std::cout.rdbuf(buffer.rdbuf());
	/// \endcode

	/// run function with output
	/// \code
	print_function();
	/// \endcode

	/// end capture stdout, back standart output
	/// \code
	std::cout.rdbuf(old);
	/// \endcode

	return buffer.str();
}

/*!
\brief Start Test arithmetic check

\see stdout_capture()
*/
BOOST_AUTO_TEST_CASE(arithmetic)
{
	/// Test arithmetic char
	/// \code
	BOOST_CHECK_EQUAL
	(
		stdout_capture([]()
		{
			print_ip(static_cast<char>(0));
		}),
		"0\n"
	);

	BOOST_CHECK_EQUAL
	(
		stdout_capture([]()
		{
			print_ip(static_cast<char>(1));
		}),
		"1\n"
	);

	BOOST_CHECK_EQUAL
	(
		stdout_capture([]()
		{
			print_ip(static_cast<char>(-1));
		}),
		"255\n"
	);

	BOOST_CHECK_EQUAL
	(
		stdout_capture([]()
		{
			print_ip(static_cast<char>(127));
		}),
		"127\n"
	);

	BOOST_CHECK_EQUAL
	(
		stdout_capture([]()
		{
			print_ip(static_cast<char>(-127));
		}),
		"129\n"
	);

	BOOST_CHECK_EQUAL
	(
		stdout_capture([]()
		{
			print_ip(static_cast<char>(-128));
		}),
		"128\n"
	);
	/// \endcode

	/// Test arithmetic short
	/// \code
	BOOST_CHECK_EQUAL
	(
		stdout_capture([]()
		{
			print_ip(static_cast<short>(0));
		}),
		"0.0\n"
	);

	BOOST_CHECK_EQUAL
	(
		stdout_capture([]()
		{
			print_ip(static_cast<short>(1));
		}),
		"0.1\n"
	);

	BOOST_CHECK_EQUAL
	(
		stdout_capture([]()
		{
			print_ip(static_cast<short>(-1));
		}),
		"255.255\n"
	);

	BOOST_CHECK_EQUAL
	(
		stdout_capture([]()
		{
			print_ip(static_cast<short>(255));
		}),
		"0.255\n"
	);

	BOOST_CHECK_EQUAL
	(
		stdout_capture([]()
		{
			print_ip(static_cast<short>(-256));
		}),
		"255.0\n"
	);

	BOOST_CHECK_EQUAL
	(
		stdout_capture([]()
		{
			print_ip(static_cast<short>(32767));
		}),
		"127.255\n"
	);

	BOOST_CHECK_EQUAL
	(
		stdout_capture([]()
		{
			print_ip(static_cast<short>(-32768));
		}),
		"128.0\n"
	);
	/// \endcode

	/// Test arithmetic int
	/// \code
	BOOST_CHECK_EQUAL
	(
		stdout_capture([]()
		{
			print_ip(static_cast<int>(0));
		}),
		"0.0.0.0\n"
	);

	BOOST_CHECK_EQUAL
	(
		stdout_capture([]()
		{
			print_ip(static_cast<int>(1));
		}),
		"0.0.0.1\n"
	);

	BOOST_CHECK_EQUAL
	(
		stdout_capture([]()
		{
			print_ip(static_cast<int>(-1));
		}),
		"255.255.255.255\n"
	);

	BOOST_CHECK_EQUAL
	(
		stdout_capture([]()
		{
			print_ip(static_cast<int>(255));
		}),
		"0.0.0.255\n"
	);

	BOOST_CHECK_EQUAL
	(
		stdout_capture([]()
		{
			print_ip(static_cast<int>(-256));
		}),
		"255.255.255.0\n"
	);

	BOOST_CHECK_EQUAL
	(
		stdout_capture([]()
		{
			print_ip(static_cast<int>(65535));
		}),
		"0.0.255.255\n"
	);

	BOOST_CHECK_EQUAL
	(
		stdout_capture([]()
		{
			print_ip(static_cast<int>(-65536));
		}),
		"255.255.0.0\n"
	);

	BOOST_CHECK_EQUAL
	(
		stdout_capture([]()
		{
			print_ip(static_cast<int>(16777215));
		}),
		"0.255.255.255\n"
	);

	BOOST_CHECK_EQUAL
	(
		stdout_capture([]()
		{
			print_ip(static_cast<int>(-16777216));
		}),
		"255.0.0.0\n"
	);
	/// \endcode

	/// Test arithmetic long
	/// \code
	BOOST_CHECK_EQUAL
	(
		stdout_capture([]()
		{
			print_ip(static_cast<long>(0));
		}),
		"0.0.0.0.0.0.0.0\n"
	);

	BOOST_CHECK_EQUAL
	(
		stdout_capture([]()
		{
			print_ip(static_cast<long>(1));
		}),
		"0.0.0.0.0.0.0.1\n"
	);

	BOOST_CHECK_EQUAL
	(
		stdout_capture([]()
		{
			print_ip(static_cast<long>(-1));
		}),
		"255.255.255.255.255.255.255.255\n"
	);

	BOOST_CHECK_EQUAL
	(
		stdout_capture([]()
		{
			print_ip(static_cast<long>(255));
		}),
		"0.0.0.0.0.0.0.255\n"
	);

	BOOST_CHECK_EQUAL
	(
		stdout_capture([]()
		{
			print_ip(static_cast<long>(-256));
		}),
		"255.255.255.255.255.255.255.0\n"
	);

	BOOST_CHECK_EQUAL
	(
		stdout_capture([]()
		{
			print_ip(static_cast<long>(65535));
		}),
		"0.0.0.0.0.0.255.255\n"
	);

	BOOST_CHECK_EQUAL
	(
		stdout_capture([]()
		{
			print_ip(static_cast<long>(-65536));
		}),
		"255.255.255.255.255.255.0.0\n"
	);

	BOOST_CHECK_EQUAL
	(
		stdout_capture([]()
		{
			print_ip(static_cast<long>(16777215));
		}),
		"0.0.0.0.0.255.255.255\n"
	);

	BOOST_CHECK_EQUAL
	(
		stdout_capture([]()
		{
			print_ip(static_cast<long>(-16777216));
		}),
		"255.255.255.255.255.0.0.0\n"
	);

	BOOST_CHECK_EQUAL
	(
		stdout_capture([]()
		{
			print_ip(static_cast<long>(4294967295));
		}),
		"0.0.0.0.255.255.255.255\n"
	);

	BOOST_CHECK_EQUAL
	(
		stdout_capture([]()
		{
			print_ip(static_cast<long>(-4294967296));
		}),
		"255.255.255.255.0.0.0.0\n"
	);

	BOOST_CHECK_EQUAL
	(
		stdout_capture([]()
		{
			print_ip(static_cast<long>(1099511627775));
		}),
		"0.0.0.255.255.255.255.255\n"
	);

	BOOST_CHECK_EQUAL
	(
		stdout_capture([]()
		{
			print_ip(static_cast<long>(-1099511627776));
		}),
		"255.255.255.0.0.0.0.0\n"
	);

	BOOST_CHECK_EQUAL
	(
		stdout_capture([]()
		{
			print_ip(static_cast<long>(281474976710655));
		}),
		"0.0.255.255.255.255.255.255\n"
	);

	BOOST_CHECK_EQUAL
	(
		stdout_capture([]()
		{
			print_ip(static_cast<long>(-281474976710656));
		}),
		"255.255.0.0.0.0.0.0\n"
	);

	BOOST_CHECK_EQUAL
	(
		stdout_capture([]()
		{
			print_ip(static_cast<long>(72057594037927935));
		}),
		"0.255.255.255.255.255.255.255\n"
	);

	BOOST_CHECK_EQUAL
	(
		stdout_capture([]()
		{
			print_ip(static_cast<long>(-72057594037927936));
		}),
		"255.0.0.0.0.0.0.0\n"
	);
	/// \endcode
}

/*!
\brief Start Test container check

\see stdout_capture()
*/
BOOST_AUTO_TEST_CASE(container)
{

	/// Test container with int elements
	/// \code
	BOOST_CHECK_EQUAL
	(
		stdout_capture([]()
		{
			print_ip(std::vector<int> {-1, 2130706433, 127, -128, 64, -64});
		}),
		"255.255.255.255\n"
		"127.0.0.1\n"
		"0.0.0.127\n"
		"255.255.255.128\n"
		"0.0.0.64\n"
		"255.255.255.192\n"
	);

	BOOST_CHECK_EQUAL
	(
		stdout_capture([]()
		{
			print_ip(std::list<int> {-1, 2130706433, 127, -128, 64, -64});
		}),
		"255.255.255.255\n"
		"127.0.0.1\n"
		"0.0.0.127\n"
		"255.255.255.128\n"
		"0.0.0.64\n"
		"255.255.255.192\n"
	);
	/// \endcode

	/// Test container with long elements
	/// \code
	BOOST_CHECK_EQUAL
	(
		stdout_capture([]()
		{
			print_ip(std::vector<long> {-1, 2130706433, 127, -128, 64, -64});
		}),
		"255.255.255.255.255.255.255.255\n"
		"0.0.0.0.127.0.0.1\n"
		"0.0.0.0.0.0.0.127\n"
		"255.255.255.255.255.255.255.128\n"
		"0.0.0.0.0.0.0.64\n"
		"255.255.255.255.255.255.255.192\n"
	);

	BOOST_CHECK_EQUAL
	(
		stdout_capture([]()
		{
			print_ip(std::list<long> {-1, 2130706433, 127, -128, 64, -64});
		}),
		"255.255.255.255.255.255.255.255\n"
		"0.0.0.0.127.0.0.1\n"
		"0.0.0.0.0.0.0.127\n"
		"255.255.255.255.255.255.255.128\n"
		"0.0.0.0.0.0.0.64\n"
		"255.255.255.255.255.255.255.192\n"
	);
	/// \endcode
}

/*!
\brief Start Test string check

\see stdout_capture()
*/
BOOST_AUTO_TEST_CASE(str)
{
	BOOST_CHECK_EQUAL
	(
		stdout_capture([]()
		{
			print_ip(std::string("abc 12.52.13.44 fsafsaf 127.0.0.1 efg"));
		}),
		"abc 12.52.13.44 fsafsaf 127.0.0.1 efg\n"
	);
}

/*!
\brief Start Test tuple check with same elements

\see stdout_capture()
*/
BOOST_AUTO_TEST_CASE(tup)
{

	/// Test tuple with int elements
	/// \code
	BOOST_CHECK_EQUAL
	(
		stdout_capture([]()
		{
			print_ip(std::make_tuple(256, 4096, 8192, 2048, 128, -1, -256, -1024, -4096, -8192));
		}),
		"0.0.1.0\n"
		"0.0.16.0\n"
		"0.0.32.0\n"
		"0.0.8.0\n"
		"0.0.0.128\n"
		"255.255.255.255\n"
		"255.255.255.0\n"
		"255.255.252.0\n"
		"255.255.240.0\n"
		"255.255.224.0\n"
	);
	/// \endcode

	/// Test tuple with long elements
	/// \code
	BOOST_CHECK_EQUAL
	(
		stdout_capture([]()
		{
			print_ip(std::make_tuple((long)256, 4096, 8192, 2048, 128, -1, -256, -1024, -4096, -8192));
		}),
		"0.0.0.0.0.0.1.0\n"
		"0.0.0.0.0.0.16.0\n"
		"0.0.0.0.0.0.32.0\n"
		"0.0.0.0.0.0.8.0\n"
		"0.0.0.0.0.0.0.128\n"
		"255.255.255.255.255.255.255.255\n"
		"255.255.255.255.255.255.255.0\n"
		"255.255.255.255.255.255.252.0\n"
		"255.255.255.255.255.255.240.0\n"
		"255.255.255.255.255.255.224.0\n"
	);
	/// \endcode
}

BOOST_AUTO_TEST_SUITE_END()


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
			print_ip(static_cast<int8_t>(0));
		}),
		"0\n"
	);

	BOOST_CHECK_EQUAL
	(
		stdout_capture([]()
		{
			print_ip(static_cast<int8_t>(1));
		}),
		"1\n"
	);

	BOOST_CHECK_EQUAL
	(
		stdout_capture([]()
		{
			print_ip(static_cast<int8_t>(0xFF));
		}),
		"255\n"
	);

	BOOST_CHECK_EQUAL
	(
		stdout_capture([]()
		{
			print_ip(static_cast<int8_t>(0x7F));
		}),
		"127\n"
	);

	BOOST_CHECK_EQUAL
	(
		stdout_capture([]()
		{
			print_ip(static_cast<int8_t>(0x81));
		}),
		"129\n"
	);

	BOOST_CHECK_EQUAL
	(
		stdout_capture([]()
		{
			print_ip(static_cast<int8_t>(0x80));
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
			print_ip(static_cast<int16_t>(0));
		}),
		"0.0\n"
	);

	BOOST_CHECK_EQUAL
	(
		stdout_capture([]()
		{
			print_ip(static_cast<int16_t>(1));
		}),
		"0.1\n"
	);

	BOOST_CHECK_EQUAL
	(
		stdout_capture([]()
		{
			print_ip(static_cast<int16_t>(0xFFFF));
		}),
		"255.255\n"
	);

	BOOST_CHECK_EQUAL
	(
		stdout_capture([]()
		{
			print_ip(static_cast<int16_t>(0x00FF));
		}),
		"0.255\n"
	);

	BOOST_CHECK_EQUAL
	(
		stdout_capture([]()
		{
			print_ip(static_cast<int16_t>(0xFF00));
		}),
		"255.0\n"
	);

	BOOST_CHECK_EQUAL
	(
		stdout_capture([]()
		{
			print_ip(static_cast<int16_t>(0x7FFF));
		}),
		"127.255\n"
	);

	BOOST_CHECK_EQUAL
	(
		stdout_capture([]()
		{
			print_ip(static_cast<int16_t>(0x8000));
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
			print_ip(static_cast<int32_t>(0));
		}),
		"0.0.0.0\n"
	);

	BOOST_CHECK_EQUAL
	(
		stdout_capture([]()
		{
			print_ip(static_cast<int32_t>(1));
		}),
		"0.0.0.1\n"
	);

	BOOST_CHECK_EQUAL
	(
		stdout_capture([]()
		{
			print_ip(static_cast<int32_t>(0xFFFFFFFF));
		}),
		"255.255.255.255\n"
	);

	BOOST_CHECK_EQUAL
	(
		stdout_capture([]()
		{
			print_ip(static_cast<int32_t>(0x000000FF));
		}),
		"0.0.0.255\n"
	);

	BOOST_CHECK_EQUAL
	(
		stdout_capture([]()
		{
			print_ip(static_cast<int32_t>(0xFFFFFF00));
		}),
		"255.255.255.0\n"
	);

	BOOST_CHECK_EQUAL
	(
		stdout_capture([]()
		{
			print_ip(static_cast<int32_t>(0x0000FFFF));
		}),
		"0.0.255.255\n"
	);

	BOOST_CHECK_EQUAL
	(
		stdout_capture([]()
		{
			print_ip(static_cast<int32_t>(0xFFFF0000));
		}),
		"255.255.0.0\n"
	);

	BOOST_CHECK_EQUAL
	(
		stdout_capture([]()
		{
			print_ip(static_cast<int32_t>(0x00FFFFFF));
		}),
		"0.255.255.255\n"
	);

	BOOST_CHECK_EQUAL
	(
		stdout_capture([]()
		{
			print_ip(static_cast<int32_t>(0xFF000000));
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
			print_ip(static_cast<int64_t>(0));
		}),
		"0.0.0.0.0.0.0.0\n"
	);

	BOOST_CHECK_EQUAL
	(
		stdout_capture([]()
		{
			print_ip(static_cast<int64_t>(1));
		}),
		"0.0.0.0.0.0.0.1\n"
	);

	BOOST_CHECK_EQUAL
	(
		stdout_capture([]()
		{
			print_ip(static_cast<int64_t>(0xFFFFFFFFFFFFFFFF));
		}),
		"255.255.255.255.255.255.255.255\n"
	);

	BOOST_CHECK_EQUAL
	(
		stdout_capture([]()
		{
			print_ip(static_cast<int64_t>(0x00000000000000FF));
		}),
		"0.0.0.0.0.0.0.255\n"
	);

	BOOST_CHECK_EQUAL
	(
		stdout_capture([]()
		{
			print_ip(static_cast<int64_t>(0xFFFFFFFFFFFFFF00));
		}),
		"255.255.255.255.255.255.255.0\n"
	);

	BOOST_CHECK_EQUAL
	(
		stdout_capture([]()
		{
			print_ip(static_cast<int64_t>(0x000000000000FFFF));
		}),
		"0.0.0.0.0.0.255.255\n"
	);

	BOOST_CHECK_EQUAL
	(
		stdout_capture([]()
		{
			print_ip(static_cast<int64_t>(0xFFFFFFFFFFFF0000));
		}),
		"255.255.255.255.255.255.0.0\n"
	);

	BOOST_CHECK_EQUAL
	(
		stdout_capture([]()
		{
			print_ip(static_cast<int64_t>(0x0000000000FFFFFF));
		}),
		"0.0.0.0.0.255.255.255\n"
	);

	BOOST_CHECK_EQUAL
	(
		stdout_capture([]()
		{
			print_ip(static_cast<int64_t>(0xFFFFFFFFFF000000));
		}),
		"255.255.255.255.255.0.0.0\n"
	);

	BOOST_CHECK_EQUAL
	(
		stdout_capture([]()
		{
			print_ip(static_cast<int64_t>(0x00000000FFFFFFFF));
		}),
		"0.0.0.0.255.255.255.255\n"
	);

	BOOST_CHECK_EQUAL
	(
		stdout_capture([]()
		{
			print_ip(static_cast<int64_t>(0xFFFFFFFF00000000));
		}),
		"255.255.255.255.0.0.0.0\n"
	);

	BOOST_CHECK_EQUAL
	(
		stdout_capture([]()
		{
			print_ip(static_cast<int64_t>(0x000000FFFFFFFFFF));
		}),
		"0.0.0.255.255.255.255.255\n"
	);

	BOOST_CHECK_EQUAL
	(
		stdout_capture([]()
		{
			print_ip(static_cast<int64_t>(0xFFFFFF0000000000));
		}),
		"255.255.255.0.0.0.0.0\n"
	);

	BOOST_CHECK_EQUAL
	(
		stdout_capture([]()
		{
			print_ip(static_cast<int64_t>(0x0000FFFFFFFFFFFF));
		}),
		"0.0.255.255.255.255.255.255\n"
	);

	BOOST_CHECK_EQUAL
	(
		stdout_capture([]()
		{
			print_ip(static_cast<int64_t>(0xFFFF000000000000));
		}),
		"255.255.0.0.0.0.0.0\n"
	);

	BOOST_CHECK_EQUAL
	(
		stdout_capture([]()
		{
			print_ip(static_cast<int64_t>(0x00FFFFFFFFFFFFFF));
		}),
		"0.255.255.255.255.255.255.255\n"
	);

	BOOST_CHECK_EQUAL
	(
		stdout_capture([]()
		{
			print_ip(static_cast<int64_t>(0xFF00000000000000));
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
			print_ip(std::vector<int32_t> {-1, 2130706433, 127, -128, 64, -64});
		}),
		"-1..2130706433..127..-128..64..-64\n"
	);

	BOOST_CHECK_EQUAL
	(
		stdout_capture([]()
		{
			print_ip(std::list<int32_t> {-1, 2130706433, 127, -128, 64, -64});
		}),
		"-1..2130706433..127..-128..64..-64\n"
	);
	/// \endcode

	/// Test container with long elements
	/// \code
	BOOST_CHECK_EQUAL
	(
		stdout_capture([]()
		{
			print_ip(std::vector<int64_t> {-1, 2130706433, 127, -128, 64, -64});
		}),
		"-1..2130706433..127..-128..64..-64\n"
	);

	BOOST_CHECK_EQUAL
	(
		stdout_capture([]()
		{
			print_ip(std::list<int64_t> {-1, 2130706433, 127, -128, 64, -64});
		}),
		"-1..2130706433..127..-128..64..-64\n"
	);
	/// \endcode

	/// Test container with embedded containers
	/// \code
	BOOST_CHECK_EQUAL
	(
		stdout_capture([]()
		{
			print_ip(std::list<std::vector<int64_t>>
			{
				{-1, 2130706433, 127, -128, 64, -64},
				{1,2,3,4}
			});
		}),
		"-1..2130706433..127..-128..64..-64..1..2..3..4\n"
	);

	BOOST_CHECK_EQUAL
	(
		stdout_capture([]()
		{
			print_ip(std::vector<std::list<int32_t>>
			{
				{-1, 2130706433, 127, -128, 64, -64},
				{1,2,3,4,5}
			});
		}),
		"-1..2130706433..127..-128..64..-64..1..2..3..4..5\n"
	);

	BOOST_CHECK_EQUAL
	(
		stdout_capture([]()
		{
			print_ip(std::vector<std::list<std::vector<int32_t>>>
			{
				{
					{-1, 2130706433, 127, -128, 64, -64},
					{1,2,3,4,5}
				},
				{
					{
						{-1, 2130706433, 127, -128, 64, -64},
						{1,2,3,4,5}
					}
				}
			});
		}),
		"-1..2130706433..127..-128..64..-64..1..2..3..4..5..-1..2130706433..127..-128..64..-64..1..2..3..4..5\n"
	);


	BOOST_CHECK_EQUAL
	(
		stdout_capture([]()
		{
			print_ip(std::list<std::vector<std::list<int64_t>>>
			{
				{
					{1,2},
					{3,4}
				},
				{
					{
						{5,6},
						{7,8}
					}
				},
				{
					{1,2},
					{3,4}
				},
				{
					{
						{5,6},
						{7,8}
					}
				}
			});
		}),
		"1..2..3..4..5..6..7..8..1..2..3..4..5..6..7..8\n"
	);

	BOOST_CHECK_EQUAL
	(
		stdout_capture([]()
		{
			print_ip(std::vector<std::string> {"1","2","3","4","5","6"});
		}),
		"1..2..3..4..5..6\n"
	);
	BOOST_CHECK_EQUAL
	(
		stdout_capture([]()
		{
			print_ip(std::list<std::string> {"1","2","3","4","5","6"});
		}),
		"1..2..3..4..5..6\n"
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
		"256..4096..8192..2048..128..-1..-256..-1024..-4096..-8192\n"
	);
	/// \endcode

	/// Test tuple with long elements
	/// \code
	BOOST_CHECK_EQUAL
	(
		stdout_capture([]()
		{
			print_ip(std::make_tuple((int64_t)256, "4096", 8192, 2048, "128", -1, -256, "-1024", -4096, -8192));
		}),
		"256..4096..8192..2048..128..-1..-256..-1024..-4096..-8192\n"
	);
	/// \endcode
}

BOOST_AUTO_TEST_SUITE_END()


/*! \file
    \brief Test for bulk
    \see bulk()
*/

#define BOOST_TEST_MODULE bulk_test

#include <boost/test/unit_test.hpp>

#include "bulk.h"
#include <chrono>
#include <thread>

BOOST_AUTO_TEST_SUITE(test_suite_main)

using namespace HW_07;

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

void file_capture(std::string path, std::string check)
{
	BOOST_CHECK_EQUAL
	(
		stdout_capture([&]()
		{
			std::ifstream ifs (path, std::ifstream::in);
			char c = ifs.get();

			while (ifs.good())
			{
				std::cout << c;
				c = ifs.get();
			}

			ifs.close();
		}), check
	);

	std::this_thread::sleep_for(std::chrono::seconds(1));
}

BOOST_AUTO_TEST_CASE(bulk_test_1)
{
	Bulk bulk;

	LOG::Console console(&bulk);
	LOG::File file(&bulk);

	std::string check = "bulk: cmd1, cmd2, cmd3\n";
	BOOST_CHECK_EQUAL
	(
		stdout_capture([&]()
		{
			bulk.Act("cmd1");
			bulk.Act("cmd2");
			bulk.Act("cmd3");
		}), check
	);
	file_capture(file.Get_file(), check);
}

BOOST_AUTO_TEST_CASE(bulk_test_2)
{
	Bulk bulk;

	LOG::Console console(&bulk);
	LOG::File file(&bulk);

	std::string check = "bulk: cmd1, cmd2, cmd3\nbulk: cmd4, cmd5\n";
	BOOST_CHECK_EQUAL
	(
		stdout_capture([&]()
		{
			bulk.Act("cmd1");
			bulk.Act("cmd2");
			bulk.Act("cmd3");
			bulk.Act("cmd4");
			bulk.Act("cmd5");
			bulk.Act("");
		}), check
	);
	file_capture(file.Get_file(), check);
}


BOOST_AUTO_TEST_CASE(bulk_test_3)
{
	Bulk bulk;

	LOG::Console console(&bulk);
	LOG::File file(&bulk);

	std::string check = "bulk: cmd1, cmd2, cmd3\nbulk: cmd4, cmd5, cmd6, cmd7\n";
	BOOST_CHECK_EQUAL
	(
		stdout_capture([&]()
		{
			bulk.Act("cmd1");
			bulk.Act("cmd2");
			bulk.Act("cmd3");
			bulk.Act("{");
			bulk.Act("cmd4");
			bulk.Act("cmd5");
			bulk.Act("cmd6");
			bulk.Act("cmd7");
			bulk.Act("}");
		}), check
	);
	file_capture(file.Get_file(), check);
}

BOOST_AUTO_TEST_CASE(bulk_test_4)
{
	Bulk bulk;

	LOG::Console console(&bulk);
	LOG::File file(&bulk);

	std::string check = "bulk: cmd1, cmd2, cmd3, cmd4, cmd5, cmd6\n";
	BOOST_CHECK_EQUAL
	(
		stdout_capture([&]()
		{
			bulk.Act("{");
			bulk.Act("cmd1");
			bulk.Act("cmd2");
			bulk.Act("{");
			bulk.Act("cmd3");
			bulk.Act("cmd4");
			bulk.Act("}");
			bulk.Act("cmd5");
			bulk.Act("cmd6");
			bulk.Act("}");
		}), check
	);
	file_capture(file.Get_file(), check);
}

BOOST_AUTO_TEST_CASE(bulk_test_5)
{
	Bulk bulk;

	LOG::Console console(&bulk);
	LOG::File file(&bulk);

	std::string check = "bulk: cmd1, cmd2, cmd3\n";
	BOOST_CHECK_EQUAL
	(
		stdout_capture([&]()
		{
			bulk.Act("cmd1");
			bulk.Act("cmd2");
			bulk.Act("cmd3");
			bulk.Act("{");
			bulk.Act("cmd4");
			bulk.Act("cmd5");
			bulk.Act("cmd6");
			bulk.Act("cmd7");
			bulk.Act("");
		}), check
	);
	file_capture(file.Get_file(), check);
}


BOOST_AUTO_TEST_SUITE_END()

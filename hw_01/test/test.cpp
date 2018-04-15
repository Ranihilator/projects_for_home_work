/*!
\file
\brief Test to check build number
*/
#include "version_library.h"

#define BOOST_TEST_MODULE helloworld_test

#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(test_suite_main)

using namespace HW_01;

BOOST_AUTO_TEST_CASE(test_version_valid)
{
	BOOST_CHECK( version() > 0 );
}

BOOST_AUTO_TEST_SUITE_END()

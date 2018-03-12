#include "library.h"
#include <random>
#include <ctime>
#define BOOST_TEST_MODULE test_filter

#include <boost/test/unit_test.hpp>

std::tuple<uint8_t,uint8_t,uint8_t,uint8_t,std::string> random_test()
{
    std::tuple<uint8_t,uint8_t,uint8_t,uint8_t,std::string> result;
    std::stringstream ss;
    static auto counter=0;

    std::mt19937 gen(std::time(0)+counter);
    counter++;

    std::get<0>(result) = gen();
    std::get<1>(result) = gen();
    std::get<2>(result) = gen();
    std::get<3>(result) = gen();

    ss << std::to_string(std::get<0>(result))<<".";
    ss << std::to_string(std::get<1>(result))<<".";
    ss << std::to_string(std::get<2>(result))<<".";
    ss << std::to_string(std::get<3>(result));

    std::get<4>(result) = ss.str();

    return std::move(result);
}

BOOST_AUTO_TEST_SUITE(test_suite_main)

BOOST_AUTO_TEST_CASE(ip_filter_test)
{
    IP_Address_Sort<std::deque> data;
    data(std::make_tuple(0,0,0,0));
    data(std::make_tuple(5,2,1,7));
    data(std::make_tuple(1,1,7,2));
    data(std::make_tuple(21,61,71,12));
    data(std::make_tuple(79,21,1,12));

    std::stringstream ss,ss_sort;
    ss << "0.0.0.0" << std::endl;
    ss << "5.2.1.7" << std::endl;
    ss << "1.1.7.2" << std::endl;
    ss << "21.61.71.12" << std::endl;
    ss << "79.21.1.12" << std::endl;
    if (data.str().str()!=ss.str())
    {
        BOOST_FAIL("Fill container without filter [ERROR]");
    }
    else
    {
        BOOST_TEST_MESSAGE("Fill container without filter [SUCCESS]");
    }

    std::sort(data.rbegin(),data.rend());
    ss_sort << "79.21.1.12" << std::endl;
    ss_sort << "21.61.71.12" << std::endl;
    ss_sort << "5.2.1.7" << std::endl;
    ss_sort << "1.1.7.2" << std::endl;
    ss_sort << "0.0.0.0" << std::endl;

    if (data.str().str()!=ss_sort.str())
    {
        BOOST_FAIL("Sort container without filter [ERROR]");
    }
    else
    {
        BOOST_TEST_MESSAGE("Sort container without filter [SUCCESS]");
    }






    IP_Address_Sort<std::deque> data_filter_task1(1);
    data_filter_task1(std::make_tuple(0,0,0,0));
    data_filter_task1(std::make_tuple(5,2,1,7));
    data_filter_task1(std::make_tuple(1,1,7,2));
    data_filter_task1(std::make_tuple(1,5,13,2));
    data_filter_task1(std::make_tuple(21,61,71,12));
    data_filter_task1(std::make_tuple(79,21,1,12));

    std::stringstream ss1,ss1_sort;
    ss1 << "1.1.7.2" << std::endl;
    ss1 << "1.5.13.2" << std::endl;
    if (data_filter_task1.str().str()!=ss1.str())
    {
        BOOST_FAIL("Fill container with filter by first byte == 1 [ERROR]");
    }
    else
    {
        BOOST_TEST_MESSAGE("Fill container with filter by first byte == 1 [SUCCESS]");
    }

    std::sort(data_filter_task1.rbegin(),data_filter_task1.rend());
    ss1_sort << "1.5.13.2" << std::endl;
    ss1_sort << "1.1.7.2" << std::endl;
    if (data_filter_task1.str().str()!=ss1_sort.str())
    {
        BOOST_FAIL("Sort container with filter by first byte == 1 [ERROR]");
    }
    else
    {
        BOOST_TEST_MESSAGE("Sort container with filter by first byte == 1 [SUCCESS]");
    }






    IP_Address_Sort<std::deque> data_filter_task2(46,70);
    data_filter_task2(std::make_tuple(0,0,0,0));
    data_filter_task2(std::make_tuple(5,2,1,7));
    data_filter_task2(std::make_tuple(46,70,7,2));
    data_filter_task2(std::make_tuple(46,70,13,2));
    data_filter_task2(std::make_tuple(21,61,71,12));
    data_filter_task2(std::make_tuple(79,21,1,12));

    std::stringstream ss2,ss2_sort;
    ss2 << "46.70.7.2" << std::endl;
    ss2 << "46.70.13.2" << std::endl;
    if (data_filter_task2.str().str()!=ss2.str())
    {
        BOOST_FAIL("Fill container with filter by first byte == 46 and second byte == 70 [ERROR]");
    }
    else
    {
        BOOST_TEST_MESSAGE("Fill container with filter by first byte == 46 and second byte == 70 [SUCCESS]");
    }

    std::sort(data_filter_task2.rbegin(),data_filter_task2.rend());
    ss2_sort << "46.70.13.2" << std::endl;
    ss2_sort << "46.70.7.2" << std::endl;
    if (data_filter_task2.str().str()!=ss2_sort.str())
    {
        BOOST_FAIL("Sort container with filter by first byte == 46 and second byte == 70 [ERROR]");
    }
    else
    {
        BOOST_TEST_MESSAGE("Sort container with filter by first byte == 46 and second byte == 70 [SUCCESS]");
    }




    IP_Address_Sort_Any<std::deque> data_filter_task3(46);
    data_filter_task3(std::make_tuple(0,46,0,0));
    data_filter_task3(std::make_tuple(5,2,1,7));
    data_filter_task3(std::make_tuple(46,70,7,2));
    data_filter_task3(std::make_tuple(46,70,13,2));
    data_filter_task3(std::make_tuple(21,61,46,12));
    data_filter_task3(std::make_tuple(79,21,1,12));

    std::stringstream ss3,ss3_sort;
    ss3 << "0.46.0.0" << std::endl;
    ss3 << "46.70.7.2" << std::endl;
    ss3 << "46.70.13.2" << std::endl;
    ss3 << "21.61.46.12" << std::endl;
    if (data_filter_task3.str().str()!=ss3.str())
    {
        BOOST_FAIL("Fill container with filter by any byte == 46 [ERROR]");
    }
    else
    {
        BOOST_TEST_MESSAGE("Fill container with filter by any byte == 46  [SUCCESS]");
    }

    std::sort(data_filter_task3.rbegin(),data_filter_task3.rend());
    ss3_sort << "46.70.13.2" << std::endl;
    ss3_sort << "46.70.7.2" << std::endl;
    ss3_sort << "21.61.46.12" << std::endl;
    ss3_sort << "0.46.0.0" << std::endl;
    if (data_filter_task3.str().str()!=ss3_sort.str())
    {
        BOOST_FAIL("Sort container with filter by any byte == 46  [ERROR]");
    }
    else
    {
        BOOST_TEST_MESSAGE("Sort container with filter by any byte == 46  [SUCCESS]");
    }
}


///Задание №3 Реализовать constexpr функцию bin_id - определения ближайшей большей степени двойки
constexpr uint64_t bin_id(uint64_t x, uint64_t t=0x8000000000000000, int c=64)
{
	return (c>=0)?((x<=t)?(bin_id(x,t>>1,--c)):(c)):(0);
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
	BOOST_STATIC_ASSERT(bin_id(1024*1024-33) == 20);
	BOOST_STATIC_ASSERT(bin_id(1024*1024) == 20);
	BOOST_STATIC_ASSERT(bin_id(1024*1024+33) == 21);
	BOOST_STATIC_ASSERT(bin_id(1024*1024*1024-127) == 30);
	BOOST_STATIC_ASSERT(bin_id(1024*1024*1024) == 30);
	BOOST_STATIC_ASSERT(bin_id(1024*1024*1024+127) == 31);
	BOOST_STATIC_ASSERT(bin_id((uint64_t)0x8000000000000000-127) == 63);
	BOOST_STATIC_ASSERT(bin_id((uint64_t)0x8000000000000000) == 63);
	BOOST_STATIC_ASSERT(bin_id((uint64_t)0x8000000000000000+127) == 64);
}


BOOST_AUTO_TEST_SUITE_END()


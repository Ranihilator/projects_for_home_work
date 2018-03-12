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


BOOST_AUTO_TEST_CASE(ip_header_test)
{
	IP_Header test_data;
	ip_address test_value;
    auto random_test_value = random_test();

    auto test = [&test_data,&test_value](std::string &&message, std::string ip)
    {
        BOOST_TEST_MESSAGE( message << " " << test_data.str() );

        if (test_data.data()!=nullptr)
        {
            if (test_data.str()==ip && *test_data.data()==test_value)
            {
                BOOST_TEST_MESSAGE("SUCCESS");
            }
            else
            {
                BOOST_TEST_MESSAGE(test_data.str());
                BOOST_TEST_MESSAGE("FAILED");
                std::string str(std::string("return must be ") + ip);
                BOOST_FAIL(str);
            }
        }
        else
        {
            BOOST_TEST_MESSAGE("FAILED");
            BOOST_FAIL("IP Header return nullptr in data method");
        }
    };

    ///Проверяем ИП заголовок с конструктором по умолчанию
    test("Creating null IP_Header","0.0.0.0");

    ///Проверяем ИП заголовок с конструктором созданный с цифровым значением ип адресса
    test_data = IP_Header(  std::get<0>(random_test_value),
                            std::get<1>(random_test_value),
                            std::get<2>(random_test_value),
                            std::get<3>(random_test_value));
    test_value = std::make_tuple(   std::get<0>(random_test_value),
                                    std::get<1>(random_test_value),
                                    std::get<2>(random_test_value),
                                    std::get<3>(random_test_value));
    test("Creating IP_Header with uint8_t constructor",std::get<4>(random_test_value));

    ///Проверяем ИП заголовок с конструктором созданный с текстовыми значением ип адресса
    random_test_value = random_test();
    test_data = IP_Header(  std::to_string(std::get<0>(random_test_value)),
                            std::to_string(std::get<1>(random_test_value)),
                            std::to_string(std::get<2>(random_test_value)),
                            std::to_string(std::get<3>(random_test_value)));
    test_value = std::make_tuple(   std::get<0>(random_test_value),
                                    std::get<1>(random_test_value),
                                    std::get<2>(random_test_value),
                                    std::get<3>(random_test_value));
    test("Creating IP_Header with string constructor",std::get<4>(random_test_value));


    IP_Header lower_data,high_data; ///Проверяем работу операторов сравнения класса

    ///Оператор ==
    BOOST_TEST_MESSAGE("testing overloading operator == IP_Header");
    for (auto i=0;i<255;++i)
    {
        high_data = IP_Header(i,i,i,i);
        lower_data = IP_Header(std::to_string(i),std::to_string(i),std::to_string(i),std::to_string(i));
        if (lower_data!=high_data)
        {
            BOOST_TEST_MESSAGE("FAILED");
            BOOST_FAIL("overloading operator == of IP_Header error ");
        }
    }
    BOOST_TEST_MESSAGE("SUCCESS");

    ///Оператор !=
    BOOST_TEST_MESSAGE("testing overloading operator != IP_Header");
    for (auto i=0;i<127;++i)
    {
        high_data = IP_Header(i,i,i,i);
        lower_data = IP_Header(std::to_string(i+128),std::to_string(i+128),std::to_string(i+128),std::to_string(i+128));
        if (lower_data==high_data)
        {
            BOOST_TEST_MESSAGE("FAILED");
            BOOST_FAIL("overloading operator != of IP_Header error ");
        }
    }
    BOOST_TEST_MESSAGE("SUCCESS");

    ///Оператор <
    BOOST_TEST_MESSAGE("testing overloading operator < IP_Header");
    for (auto i=0;i<127;++i)
    {
        high_data = IP_Header(i,i,i,i);
        lower_data = IP_Header(std::to_string(i+128),std::to_string(i+128),std::to_string(i+128),std::to_string(i+128));
        if (lower_data<high_data)
        {
            BOOST_TEST_MESSAGE("FAILED");
            BOOST_FAIL("overloading operator < of IP_Header error ");
        }

        lower_data = high_data;
        if (lower_data<high_data)
        {
            BOOST_TEST_MESSAGE("FAILED");
            BOOST_FAIL("overloading operator < of IP_Header error ");
        }
    }
    BOOST_TEST_MESSAGE("SUCCESS");

    ///Оператор <=
    BOOST_TEST_MESSAGE("testing overloading operator <= IP_Header");
    for (auto i=0;i<127;++i)
    {
        high_data = IP_Header(i,i,i,i);
        lower_data = IP_Header(std::to_string(i+128),std::to_string(i+128),std::to_string(i+128),std::to_string(i+128));
        if (lower_data<=high_data)
        {
            BOOST_TEST_MESSAGE("FAILED");
            BOOST_FAIL("overloading operator <= of IP_Header error ");
        }

        lower_data = high_data;
        if (lower_data<=high_data)
        {
            if (lower_data==high_data)
            {}
            else
            {
                BOOST_TEST_MESSAGE("FAILED");
                BOOST_FAIL("overloading operator <= of IP_Header error ");
            }
        }
    }
    BOOST_TEST_MESSAGE("SUCCESS");


    ///Оператор >
    BOOST_TEST_MESSAGE("testing overloading operator > IP_Header");
    for (auto i=0;i<127;++i)
    {
        lower_data = IP_Header(i,i,i,i);
        high_data = IP_Header(std::to_string(i+128),std::to_string(i+128),std::to_string(i+128),std::to_string(i+128));
        if (lower_data>high_data)
        {
            BOOST_TEST_MESSAGE("FAILED");
            BOOST_FAIL("overloading operator > of IP_Header error ");
        }

        lower_data = high_data;
        if (lower_data>high_data)
        {
            BOOST_TEST_MESSAGE("FAILED");
            BOOST_FAIL("overloading operator > of IP_Header error ");
        }
    }
    BOOST_TEST_MESSAGE("SUCCESS");

    ///Оператор >=
    BOOST_TEST_MESSAGE("testing overloading operator >= IP_Header");
    for (auto i=0;i<127;++i)
    {
        lower_data = IP_Header(i,i,i,i);
        high_data = IP_Header(std::to_string(i+128),std::to_string(i+128),std::to_string(i+128),std::to_string(i+128));
        if (lower_data>=high_data)
        {
            BOOST_TEST_MESSAGE("FAILED");
            BOOST_FAIL("overloading operator >= of IP_Header error ");
        }

        lower_data = high_data;
        if (lower_data>=high_data)
        {
            if (lower_data==high_data)
            {}
            else
            {
                BOOST_TEST_MESSAGE("FAILED");
                BOOST_FAIL("overloading operator >= of IP_Header error ");
            }
        }
    }
    BOOST_TEST_MESSAGE("SUCCESS");
}

BOOST_AUTO_TEST_CASE(ip_filter_test)
{
    IP_List<std::deque,IP_Filter<1>> data_filter_task1;         ///Список ИП адрессов в отсортированном виде по первому байту
    IP_List<std::deque,IP_Filter<46,70>> data_filter_task2;     ///Список ИП адрессов в отсортированном виде по первому и второму байту
    IP_List<std::deque,IP_Filter_Any<46>> data_filter_task3;    ///Список ИП адрессов в отсортированном виде по любому байту

    IP_List<std::deque> data({&data_filter_task1,&data_filter_task2,&data_filter_task3});   ///Общий Список ИП адрессов со связанными списками

    BOOST_TEST_MESSAGE("Fill IP_List and check filters");

    data.push_back(IP_Header(127,0,0,1));
    data.push_back(IP_Header(127,169,0,1));

    data.push_back(IP_Header(1,169,0,1));
    data.push_back(IP_Header(1,169,2,1));

    data.push_back(IP_Header(46,70,0,1));
    data.push_back(IP_Header(46,70,0,2));
    data.push_back(IP_Header(9,6,0,46));

    std::stringstream ss,ss1,ss2,ss3;
    ss << "127.0.0.1" << std::endl;
    ss << "127.169.0.1" << std::endl;
    ss << "1.169.0.1" << std::endl;
    ss << "1.169.2.1" << std::endl;
    ss << "46.70.0.1" << std::endl;
    ss << "46.70.0.2" << std::endl;
    ss << "9.6.0.46" << std::endl;

    if (data.str()!=ss.str())
    {
        BOOST_FAIL("IP_List without filter is not equal ");
    }
    else
    {
        BOOST_TEST_MESSAGE(data.str());
        BOOST_TEST_MESSAGE("IP_List without filter output SUCCESS");
    }

    ss1 << "1.169.0.1" << std::endl;
    ss1 << "1.169.2.1" << std::endl;
    if (data_filter_task1.str()!=ss1.str())
    {
        BOOST_FAIL("IP_List with filter (first byte == 1) is not equal ");
    }
    else
    {
        BOOST_TEST_MESSAGE(data_filter_task1.str());
        BOOST_TEST_MESSAGE("IP_List with (first byte == 1) filter output SUCCESS");
    }

    ss2 << "46.70.0.1" << std::endl;
    ss2 << "46.70.0.2" << std::endl;
    if (data_filter_task2.str()!=ss2.str())
    {
        BOOST_FAIL("IP_List with filter (first byte == 46 and second byte == 70) is not equal ");
    }
    else
    {
        BOOST_TEST_MESSAGE(data_filter_task2.str());
        BOOST_TEST_MESSAGE("IP_List with (first byte == 46 and second byte == 70) filter output SUCCESS");
    }

    ss3 << "46.70.0.1" << std::endl;
    ss3 << "46.70.0.2" << std::endl;
    ss3 << "9.6.0.46" << std::endl;
    if (data_filter_task3.str()!=ss3.str())
    {
        BOOST_FAIL("IP_List with filter (any byte == 46) is not equal ");
    }
    else
    {
        BOOST_TEST_MESSAGE(data_filter_task3.str());
        BOOST_TEST_MESSAGE("IP_List with (any byte == 46) filter output SUCCESS");
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


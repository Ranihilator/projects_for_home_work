#include "filter.h"
#include <random>
#include <ctime>
#define BOOST_TEST_MODULE test_filter

#include <boost/test/unit_test.hpp>

using namespace HW_02::FILTER;

auto random_test(std::string left_dust=std::string(), std::string right_dust=std::string())
{
    auto result = std::tuple<ip_address,std::string>();
    std::stringstream ss;
    static auto counter=0;

    std::mt19937 gen(std::time(0)+counter);
    counter++;

    ss << left_dust;

    auto ip=ip_address();
    std::get<0>(ip) = gen();
    std::get<1>(ip) = gen();
    std::get<2>(ip) = gen();
    std::get<3>(ip) = gen();

    ss << std::to_string(std::get<0>(ip))<<".";
    ss << std::to_string(std::get<1>(ip))<<".";
    ss << std::to_string(std::get<2>(ip))<<".";
    ss << std::to_string(std::get<3>(ip));
    ss << right_dust;

    std::get<0>(result) = std::move(ip);
    std::get<1>(result) = ss.str();

    return std::move(result);
}

BOOST_AUTO_TEST_SUITE(test_suite_main)

BOOST_AUTO_TEST_CASE(ip_filter_test)
{
    ///Регулярное выражение для поиска ип адресса в веденной строке
    std::regex ip_filter (FILTER_REGEX);

    BOOST_REQUIRE_THROW(split_ip("",ip_filter),std::invalid_argument);
    BOOST_REQUIRE_THROW(split_ip("fsafsafsafsa",ip_filter),std::invalid_argument);
    BOOST_REQUIRE_THROW(split_ip("1,2,3,4",ip_filter),std::invalid_argument);
    BOOST_REQUIRE_THROW(split_ip("a.b.c.d",ip_filter),std::invalid_argument);
    BOOST_REQUIRE_THROW(split_ip("1.2.3.4a",ip_filter),std::invalid_argument);
    BOOST_REQUIRE_THROW(split_ip("f1.2.3.4",ip_filter),std::invalid_argument);
    BOOST_REQUIRE_THROW(split_ip("1.a2.3.4",ip_filter),std::invalid_argument);
    BOOST_REQUIRE_THROW(split_ip("1.2.s3.4",ip_filter),std::invalid_argument);

    auto check_correct = [&ip_filter](std::string &&left_dust, std::string &&right_dust)
    {
        auto result = random_test(left_dust,right_dust);
        BOOST_CHECK(split_ip(std::move(std::get<1>(result)),ip_filter)==std::get<0>(result));
    };
    check_correct("","");
    check_correct(""," 1.2.3.4");
    check_correct(""," 64,84,97,63");
    check_correct("65,86,87,96 "," 65,44,27,1");
    check_correct("ljhgcfcg "," gdffghjk");
    check_correct("5 .86.97.76 "," 0.4 .85.123");
    check_correct("5.86.97. 76 "," 0.4.85. 123");




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
    BOOST_STATIC_ASSERT(bin_id((uint64_t)0xFFFFFFFFFFFFFFFF) == 64);
}


BOOST_AUTO_TEST_SUITE_END()


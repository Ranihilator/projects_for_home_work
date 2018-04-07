/*!
\file
\brief Основная работа

вызов функции version
*/
#define REBIND
#include "container.h"

#include <iostream>
#include <map>
#include <array>
#include <type_traits>
#include <algorithm>

namespace HW_03
{

constexpr auto factorial(auto n) -> decltype(n)
{
	return n > 0 ? n * factorial(n - 1) : 1;
}

auto make_factorial_value = [i=0] () mutable
{
    auto f = factorial(i);
    auto value = std::make_pair(i,f);
    ++i;
    return value;
};

void Map_Standart()
{
    std::map<uint64_t, uint64_t> data;

    std::generate_n
    (
        std::inserter(data, std::begin(data)),
        10,
        make_factorial_value
    );
}

void Map_Custom()
{
    std::map<uint64_t,uint64_t,std::less<uint64_t>, ALLOCATOR::allocator<std::pair<uint64_t, uint64_t>,10>> data;

	std::generate_n
	(
        std::inserter(data, std::begin(data)),
        10,
        make_factorial_value
    );

    for (auto &i : data)
        std::cout << i.first << " " << i.second << std::endl;
}

void Container_Standart()
{
    CONTAINER::container<uint64_t> data;

    for (auto i = 0; i < 10; ++i)
    {
        data.push_back(i);
    }
}

void Container_Allocator()
{
    CONTAINER::container<uint64_t, ALLOCATOR::allocator<uint64_t,10>> data;

    for (auto i = 0; i < 10; ++i)
    {
        data.push_back(i);
    }

    for (decltype(data.size()) i = 0; i < data.size(); ++i)
    {
        std::cout << data.at(i) << std::endl;
	}
}

}

using namespace HW_03;

int main()
{
    try
    {
        Map_Standart();
        Map_Custom();
        Container_Standart();
        Container_Allocator();
    }
    catch (...)
    {
        std::cout << "default catch" << std::endl;
    }
	return 0;
}

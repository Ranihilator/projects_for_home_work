/*!
\file
\brief application allocator example

allocator
- fill the std::map 10 elements with std::allocator (each element is factorial from counter)
- fill the std::map 10 elements with Allocator::allocator and stdout (each element is factorial from counter)
- fill the CONTAINER::container 10 elements with std::allocator (each element is counter's state)
- fill the CONTAINER::container 10 elements with Allocator::allocator and stdout (each element is counter's state)
*/

#include "container.h"
#include <iostream>
#include <map>
#include <array>
#include <type_traits>
#include <algorithm>

namespace HW_03
{

/*!
\brief factorial calculate
\param[in] n digit
\return factorial result
*/
template <class T>
constexpr decltype(auto) factorial(T n) -> decltype(n)
{
	return n > 0 ? n * factorial(n - 1) : 1;
}

/*!
\brief calculate factorial with increment counters
\details lamda mutable function for counter `i` 
mutable lamda for `i` because `i` is const
\return factorial result
*/
auto make_factorial_value = [i = 0] () mutable
                            {
                                auto f = factorial(i);
                                auto value = std::make_pair(i, f);
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
	std::map<uint64_t, uint64_t, std::less<uint64_t>, ALLOCATOR::allocator < std::pair<uint64_t, uint64_t>, 10 >> data;

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
		data.push_back(i);
}

void Container_Allocator()
{
	CONTAINER::container<uint64_t, ALLOCATOR::allocator<uint64_t, 10 >> data;

	for (auto i = 0; i < 10; ++i)
		data.push_back(i);

	for (decltype(data.size()) i = 0; i < data.size(); ++i)
		std::cout << data.at(i) << std::endl;
}

}

using namespace HW_03;

/*!
\brief Start program

\param[in] argc argument's count
\param[in] argv array of arguments
\return process code
*/
int main(int argc, char* argv[])
{
	try
	{
		Map_Standart();
		Map_Custom();
		Container_Standart();
		Container_Allocator();
	}
	catch (std::bad_alloc)
	{
		std::cout << "bad allocate" << std::endl;
	}
	return 0;
}

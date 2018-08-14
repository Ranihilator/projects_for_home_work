/*!
\file
\brief Header template print_ip function's

\details print ip address to stdout
*/

#pragma once

#include "tuple.h"

#include <list>
#include <vector>
#include <type_traits>

/// Home work #4 (print ip)
namespace HW_04
{

/// Print IP template
namespace PRINT
{

using namespace std;
using namespace TUPLE;

/*!
\brief Print ip address to stdout
\details Printing(reference) byte sequence to ip address format
\param[in] arg input data
\tparam T Type of data
\return void
*/
template <class T>
enable_if_t
<
	is_integral<typename std::decay<T>::type>::value,
	void
>
print_ip (const T arg, bool is_number = true)
{
	const auto size = sizeof(T);
	static_assert(size > 0, "T must be > 0");

	if (!is_number)
	{
		if (size == 1)
			cout << static_cast<int>(arg);
		else
			cout << arg;
		return;
	}

	stringstream str;

	for (auto i = 1; i <= size; ++i)
    {
		if (str.tellp() != 0)
			str << '.';

		uint8_t raw = arg >> ((size - i) * 8);
		str << static_cast<int>(raw);
	}

	cout << str.str() << endl;
}

/*!
\brief Print text
\param[in] arg input data
\tparam T Type of data
\return void
*/
template <class T>
enable_if_t
<
	is_same<typename std::decay<T>::type, string>::value,
	void
>
print_ip (const T arg, bool new_line = true)
{
	cout << arg;
	if (new_line)
		cout << endl;
}

/*!
\brief Print ip address to stdout from containers
\details Print each element from containers.

Each element is byte sequence ip address format.

\param[in] arg input data
\tparam T Type of data
\return void
*/
template <class T>
enable_if_t
<
	is_same<typename std::decay<T>::type, vector<typename std::decay<T>::type::value_type>>::value ||
	is_same<typename std::decay<T>::type, list<typename std::decay<T>::type::value_type>>::value,
	void
>
print_ip (const T arg, bool is_first = true)
{
    for (auto i = arg.begin(); i != arg.end(); ++i)
	{
		print_ip(*i, false);
		if (std::next(i)!=arg.end())
			cout << "..";
	}

	if (is_first)
		cout << endl;
}

/*!
\brief Print ip address to stdout from tuple
\details Print each element from tuple's any type format.

Each element is byte sequence ip address format.

\see TUPLE::is_specialization
\see print_tuple

\param[in] arg input data
\tparam T Type of data
\return void
*/
template <class T>
enable_if_t
<
	is_specialization<typename std::decay<T>::type, tuple>::value,
	void
> print_ip (T arg)
{
	stringstream buffer;
	print_tuple<std::tuple_size<T>::value, T>()(arg, buffer);

	cout << buffer.str() << endl;
}

}

}

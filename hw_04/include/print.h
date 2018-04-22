/*!
\file
\brief Header template print_ip function's

\details print ip address to stdout
*/

#pragma once

#include "tuple.h"

#include <list>
#include <vector>

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
\details Printing byte sequence to ip address format
\param[in] arg input data
\return void
*/
template <class T>
enable_if_t
<
	is_arithmetic<T>::value,
	void
> print_ip (const T &&arg)
{
	uint8_t size = sizeof(T);
	uint8_t *data = (uint8_t*)&arg;

	stringstream str;

	for (auto i = size - 1; i >= 0; --i)
	{
		if (str.tellp() != 0)
			str << ".";

		str << static_cast<int64_t>(data[i]);
	}

	cout << str.str() << endl;
}

/*!
\brief Print text
\param[in] arg input data
\return void
*/
template <class T>
enable_if_t
<
	is_same<T, string>::value,
	void
>
print_ip (const T arg)
{
	cout << arg << endl;
}

/*!
\brief Print ip address to stdout from containers
\details Print each element from containers.

Each element is byte sequence ip address format.

\param[in] arg input data
\return void
*/
template <class T>
enable_if_t
<
	is_same<T, vector<typename T::value_type>>::value ||
	is_same<T, list<typename T::value_type>>::value,
	void
>
print_ip (const T &arg)
{
	for (auto const &i : arg)
		print_ip(static_cast<typename T::value_type>(i));
}

/*!
\brief Print ip address to stdout from tuple
\details Print each element from tuple's single type format.

Each element is byte sequence ip address format.

\see TUPLE::is_specialization
\see print_tuple

\param[in] arg input data
\return void
*/
template <class T>
enable_if_t
<
	is_specialization<T, tuple>::value,
	void
> print_ip (T &&arg)
{
	static_assert(std::tuple_size<T>::value > 0, "tuple size must > 0");

	using type = typename std::tuple_element<0, T>::type;

	std::list<type> buffer;
	print_tuple<std::tuple_size<T>::value, T, type>()(arg, buffer);

	print_ip(buffer);
}

}

}

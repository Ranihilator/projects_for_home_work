/*!
\file
\brief Header template tuple

\details fill list from tuple container's
*/

#pragma once

#include <tuple>
#include <iostream>
#include <sstream>
#include <list>

namespace HW_04
{

namespace PRINT
{

using std::stringstream;
using std::get;
using std::false_type;
using std::true_type;

/// Tuple template
namespace TUPLE
{

	/*!
	\brief specialization for single element
	*/
	template
	<
		class T,							/// T -> simply type
		template <class...> class A			/// std::tuple -> template < class... Types > class tuple;
	>
	struct is_specialization:				/// False tuple
		false_type
	{};

	/*!
	\brief specialization for tuple
	*/
	template
	<
		class... T,							/// T -> variadic type
		template<class...> class A			/// std::tuple -> template < class... Types > class tuple;
	>
	struct is_specialization				/// True tuple
	<
		A <T...>,							/// A<T...> -> std::tuple<...>
		A									/// A -> std::tuple
	>:
		true_type
	{};
}

/*!
\brief fill list from tuple
\details enumearate all tuple element, and copy to list
\param[in] arg input data
\param[in] buffer list container
\tparam index number of tuple
\tparam T Type of data
\tparam size of tuple
\return void
*/
template<size_t index, class T, size_t size = index>
struct print_tuple
{
	void operator()(const T &arg, stringstream &buffer)
	{
		print_tuple < index - 1, T, size> ()(arg, buffer);
		buffer << get < index - 1 > (arg);

		if (index < size)
			buffer << '.';
	}
};

/*!
\brief empty tuple
\details template finish
\param[in] arg input data
\param[in] buffer list container
\tparam T Type of data
\tparam T size of tuple
\return void
*/
template<class T, size_t size>
struct print_tuple<0, T, size>
{
	void operator()(const T &arg, stringstream &buffer)
	{}
};

}

}

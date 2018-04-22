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

using namespace std;

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
\return void
*/
template<size_t index, class T, class Q, size_t size = index>
struct print_tuple
{
	void operator()(T &arg, std::list<Q> &buffer)
	{
		print_tuple < index - 1, T, Q, size> ()(arg, buffer);
		buffer.emplace_back(std::get < index - 1 > (arg));
	}
};

/*!
\brief empty tuple
\details template finish
\param[in] arg input data
\param[in] buffer list container
\return void
*/
template<class T, class Q, size_t size>
struct print_tuple<0, T, Q, size>
{
	void operator()(T &arg, std::list<Q> &buffer)
	{}
};

}

}

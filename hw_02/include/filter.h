/*!
\file
\brief Header of ip address filter

*/
#pragma once

#include <cassert>
#include <cstdlib>
#include <iostream>
#include <string>
#include <list>
#include <functional>
#include <vector>
#include <deque>
#include <set>
#include <regex>
#include <tuple>
#include <algorithm>
#include <initializer_list>

/// Home work #2 (filtering ip address)
namespace HW_02
{

/// Filter algorithm
namespace FILTER
{

template <class T = uint8_t>
using ip_address = std::tuple<T, T, T, T>;  ///< IP address type in tuple format

enum ip_octer
{
	ANY_OCTET = -1,
	FIRST_OCTET = 0,
	SECOND_OCTET = 1,
	THIRD_OCTET = 2,
	FOUR_OCTER = 3
};

#define FILTER_REGEX                           \
"\\b(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\." \
"(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\."    \
"(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\."    \
"(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\b"    \
""

/*!
operator output ip address
\param[in] out output stream
\param[in] ip ip address
\return output stream
*/
std::ostream& operator<<(std::ostream &out, const ip_address<uint8_t> &ip)
{
	out << static_cast<int>(std::get<FIRST_OCTET>(ip)) << '.'
		<< static_cast<int>(std::get<SECOND_OCTET>(ip)) << '.'
		<< static_cast<int>(std::get<THIRD_OCTET>(ip)) << '.'
		<< static_cast<int>(std::get<FOUR_OCTER>(ip)) << std::endl;
	return out;
}

/*!
\brief Sorting and unsorting ip address class

\details Add ip address by mask.
*/
class IP_Address_Sort
{
public:
	IP_Address_Sort	(const int n0 = ANY_OCTET,
					const int n1 = ANY_OCTET,
					const int n2 = ANY_OCTET,
					const int n3 = ANY_OCTET
					):
		N(std::make_tuple(n0, n1, n2, n3))
	{}

	auto operator<<(const ip_address<uint8_t>& val)
	{
		bool flag = false;
		if	(
			std::get<FIRST_OCTET>(this->N) == ANY_OCTET &&
			std::get<SECOND_OCTET>(this->N) == ANY_OCTET &&
			std::get<THIRD_OCTET>(this->N) == ANY_OCTET &&
			std::get<FOUR_OCTER>(this->N) == ANY_OCTET
			)
		{
			this->address.insert(val);
			flag = true;
		}
		else
		{
			if	(
				(std::get<FIRST_OCTET>(val) == std::get<FIRST_OCTET>(this->N) || std::get<FIRST_OCTET>(this->N) == ANY_OCTET) &&
				(std::get<SECOND_OCTET>(val) == std::get<SECOND_OCTET>(this->N) || std::get<SECOND_OCTET>(this->N) == ANY_OCTET) &&
				(std::get<THIRD_OCTET>(val) == std::get<THIRD_OCTET>(this->N) || std::get<THIRD_OCTET>(this->N) == ANY_OCTET) &&
				(std::get<FOUR_OCTER>(val) == std::get<FOUR_OCTER>(this->N) || std::get<FOUR_OCTER>(this->N) == ANY_OCTET)
				)
			{
				this->address.insert(val);
				flag = true;
			}
		}
		return flag;
	}

	auto dump()
	{
		std::stringstream stream;

		for (auto &i : address)
			stream << i;

		return stream;
	}

private:
	const ip_address<int16_t> N;

	std::multiset<ip_address<uint8_t>, std::greater_equal<ip_address<uint8_t>>> address;
};

/*!
\brief Sorting ip address by any byte

\details Add ip address by mask.
*/
class IP_Address_Sort_Any
{
public:
	explicit IP_Address_Sort_Any(const int n):
		N(n)
	{}

	auto operator<<(const ip_address<uint8_t>& val)
	{
		if (
			std::get<FIRST_OCTET>(val) == N ||
			std::get<SECOND_OCTET>(val) == N ||
			std::get<THIRD_OCTET>(val) == N ||
			std::get<FOUR_OCTER>(val) == N
			)
		{
			this->address.insert(val);
			return true;
		}
		return false;
	}

	auto dump()
	{
		std::stringstream stream;

		for (auto &i : address)
			stream << i;

		return stream;
	}

private:
	const uint8_t N;
	std::multiset<ip_address<uint8_t>, std::greater_equal<ip_address<uint8_t>>> address;
};

/*!
\brief Get ip address from string stream
\param[in] line string contain ip address
\param[in] filter regex string
\see HW_02::FILTER::ip_address
\return ip address
*/
auto split_ip(const std::string &line, std::regex &filter)
{
	static std::smatch pieces;

	std::regex_search(line, pieces, filter);
	auto value = ip_address<uint8_t>();
	if (pieces.size() > std::tuple_size<ip_address<uint8_t>>::value)
		value = std::make_tuple	(
									std::stoi(pieces[FIRST_OCTET + 1]),
									std::stoi(pieces[SECOND_OCTET + 1]),
									std::stoi(pieces[THIRD_OCTET + 1]),
									std::stoi(pieces[FOUR_OCTER + 1])
								);
	else
		throw std::invalid_argument( "wrong ip format" );

	return value;
}

}

}

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
#include <vector>
#include <deque>
#include <regex>
#include <tuple>
#include <algorithm>
#include <initializer_list>

namespace HW_02
{

namespace FILTER
{

using ip_address = std::tuple<uint8_t, uint8_t, uint8_t, uint8_t>;  ///< IP address type in tuple format

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
std::ostream& operator<<(std::ostream &out, const ip_address &ip)
{
	out << (int)std::get<0>(ip) << "."
	    << (int)std::get<1>(ip) << "."
	    << (int)std::get<2>(ip) << "."
	    << (int)std::get<3>(ip) << std::endl;
	return out;
}

/*!
\brief Sorting and unsorting ip address class

\details Add ip address by mask.
*/
struct IP_Address_Sort: public std::deque<ip_address>
{
	IP_Address_Sort(const int n0 = -1, const int n1 = -1, const int n2 = -1, const int n3 = -1):
		N0(n0), N1(n1), N2(n2), N3(n3)
	{}

	auto operator<<(const ip_address& val)
	{
		bool flag = false;
		if (N0 < 0 && N1 < 0 && N2 < 0 && N3 < 0)
		{
			this->push_back(val);
			flag = true;
		}
		else
		{
			if ( (std::get<0>(val) == N0 || N0 < 0) && (std::get<1>(val) == N1 || N1 < 0) && (std::get<2>(val) == N2 || N2 < 0) && (std::get<3>(val) == N3 || N3 < 0))
			{
				this->push_back(val);
				flag = true;
			}
		}
		return flag;
	}

	const int N0, N1, N2, N3;
};

/*!
\brief Sorting ip address by any byte

\details Add ip address by mask.
*/
struct IP_Address_Sort_Any: public std::deque<ip_address>
{
	IP_Address_Sort_Any(const int n):
		N(n)
	{}

	auto operator<<(const ip_address& val)
	{
		if (std::get<0>(val) == N || std::get<1>(val) == N || std::get<2>(val) == N || std::get<3>(val) == N)
		{
			this->push_back(val);
			return true;
		}
		return false;
	}

	const uint8_t N;
};

/*!
\brief Get ip address from string stream
\param[in] line string contain ip address 
\param[in] filter regex string
\see HW_02::FILTER::ip_address
\return ip address
*/
auto split_ip(std::string &&line, std::regex &filter)
{
	static std::smatch pieces;

	std::regex_search(line, pieces, filter);
	auto value = ip_address();
	if (pieces.size() >= 5)
		value = std::make_tuple(std::stoi(pieces[1]), std::stoi(pieces[2]), std::stoi(pieces[3]), std::stoi(pieces[4]));
	else
		throw std::invalid_argument( "wrong ip format" );

	return std::move(value);
}


}

}
